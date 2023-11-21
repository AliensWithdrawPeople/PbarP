import jinja2
import json
import pathlib

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, collinear_results_data, GeGm_Fit_Result_json, templates, root_folder

GeGm = json.loads(GeGm_Fit_Result_json.read_text())
MC_info = json.loads(MC_info_path.read_text())
vis_xsec_data = json.loads(collinear_results_data.read_text())

def eval_eff(elabel: str)->tuple[float, float]:
    if elabel not in GeGm.keys():
        raise KeyError(f'No GeGm for elabel = {elabel}')
    
    if GeGm[elabel]['status'] is not True:
        raise ValueError(f'GeGm fit status is {GeGm[elabel]["status"]}') 
    info = GeGm[elabel]
    
    ge, ge_error = info['Ge2']
    gm, gm_error = info['Gm2']
    
    ge_frac = ge / (ge + gm)
    gm_frac = gm / (ge + gm)
    
    mc = list(filter(lambda run: run[1]['elabel'] == elabel, MC_info.items()))
    if len(mc) == 0:
        raise KeyError(f"No MC for elabel = {elabel}")
    if len(mc) != 2:
        raise KeyError(f"There must be exactly two MC files for elabel = {elabel}")
    ge_mc_num = 0 if mc[0][1]['Ge^2'] != 0 else 1
    gm_mc_num = 1 if mc[0][1]['Ge^2'] != 0 else 0
    
    eff_ge = mc[ge_mc_num][1]['eff']
    eff_gm = mc[gm_mc_num][1]['eff']
    eff = eff_ge * ge_frac + eff_gm * gm_frac
    eff_error = (((eff_ge + eff_gm) * gm / (ge + gm)**2)**2 * ge_error**2 + 
                 ((eff_ge + eff_gm) * ge / (ge + gm)**2)**2 * gm_error**2 + 
                 ge_frac**2 * (eff_ge * (1 - eff_ge) / (mc[ge_mc_num][1]['events'])**0.5)**2 + 
                 gm_frac**2 * (eff_gm * (1 - eff_gm) / (mc[gm_mc_num][1]['events'])**0.5)**2 )**0.5
    return eff, eff_error


res = []
for elabel, xsec in vis_xsec_data.items():
    if xsec['nominal_energy'] < 950 or xsec['season'][-4:] == '2017':
        continue
    
    eff, eff_err = eval_eff(elabel)
    xsection, xsection_err = xsec["cross section"], xsec["cross section error"]
    res.append((xsec['season'], xsec['energy'], round(xsec["cross section"] / eff, 4), round(((xsection_err / eff)**2 + (xsection * eff_err / eff**2)**2)**0.5, 4)))

res.sort(key=lambda x: x[0])

seasons = dict()
for season, energy, xsection, xsection_err in res:
    if season not in seasons.keys():
        seasons[season] = {'energy' : [], 'xsec' : [], 'xsec_error' : []}
    seasons[season]['energy'].append(str(energy))
    seasons[season]['xsec'].append(str(xsection))
    seasons[season]['xsec_error'].append(str(xsection_err))


for season, vals in seasons.items():
    vals['name'] = f'season{season[-4:]}'
    vals['energy'] = f"std::vector<double> energy_{vals['name']}" + " = {" + ', '.join(vals['energy']) + '}; // MeV'
    vals['xsec'] = f"std::vector<double> xsec_{vals['name']}" + " = {" + ', '.join(vals['xsec']) + '}; // nb'
    vals['xsec_error'] = f"std::vector<double> xsec_err_{vals['name']}" + " = {" + ', '.join(vals['xsec_error']) + '}; // nb'
season_list = [vals for _, vals in seasons.items()]

def render(data, template_filename, output_filename):
    with open(template_filename) as file_:
        template = jinja2.Template(file_.read())
    rendered_content = template.render(seasons=data)
    with open(output_filename, "w") as file:
        file.write(rendered_content)

template_filename = pathlib.Path(templates, 'xsec_coll.cpp.jinja')
output_filename = pathlib.Path(root_folder, 'graph_drawing_scripts/xsec_coll.cpp')

render(season_list, template_filename, output_filename)
