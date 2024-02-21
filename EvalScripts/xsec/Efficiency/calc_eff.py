import jinja2
import json
import pathlib

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, collinear_results_data, stars_results_data, GeGm_Fit_Result_json, templates, root_folder

# type = "coll"
type = "stars"

type_name_official = 'collinear' if type == "coll" else 'annihilation'
results_data = collinear_results_data if type == "coll" else stars_results_data
eff_key_name = 'eff' if type == "coll" else 'eff_stars'
eff_scale = (1, 0) if type == "coll" else (0.515, 0.0129)
eff_scale = (1, 0) if type == "coll" else (1, 0)

GeGm = json.loads(GeGm_Fit_Result_json.read_text())
MC_info = json.loads(MC_info_path.read_text())
vis_xsec_data = json.loads(results_data.read_text())

def load_MC_info(elabel: str):
    if elabel not in GeGm.keys():
        raise KeyError(f'No GeGm for elabel = {elabel}')
    
    if GeGm[elabel]['status'] is not True:
        raise ValueError(f'GeGm fit status is {GeGm[elabel]["status"]}') 
    info = GeGm[elabel]
    ge, ge_error = info['Ge2']
    gm, gm_error = info['Gm2']
    return ge, ge_error, gm, gm_error

def eval_eff(elabel: str, ge: float, ge_error: float, gm: float, gm_error: float, eff_scale: tuple[float, float] = (1, 0))->tuple[float, float]:
    """Evaluate selection efficiency.

    Parameters
    ----------
    elabel : str
        Elabel of the energy point.
    ge : float
        G_{e} factor. == 1 if E < 950 MeV
    ge_error : float
        Error of G_{e} factor
    gm : float
        G_{m} factor. == 1 if E < 950 MeV
    gm_error : float
        Error of G_{m} factor
    eff_scale : tuple[float, float], optional
        scale for annihilation events = sigma^{not corrected eff}_{stars} / sigma_{coll}, by default (1, 0)

    Returns
    -------
    tuple[float, float]
        efficiency, error of the efficiency

    Raises
    ------
    KeyError
        There must be exactly two MC files for elabel. 
    """
    ge_frac = ge / (ge + gm)
    gm_frac = gm / (ge + gm)
    
    mc = list(filter(lambda run: run[1]['elabel'] == elabel, MC_info.items()))
    if len(mc) == 0:
        if int(elabel[:3]) < 939:
            return 1, 0
        raise KeyError(f"No MC for elabel = {elabel}")
    if len(mc) != 2:
        raise KeyError(f"There must be exactly two MC files for elabel = {elabel}")
    
    ge_mc_num = 0 if mc[0][1]['Ge^2'] != 0 else 1
    gm_mc_num = 1 if mc[0][1]['Ge^2'] != 0 else 0
    
    eff_ge = mc[ge_mc_num][1][eff_key_name]
    eff_gm = mc[gm_mc_num][1][eff_key_name]
    
    eff = eff_ge * ge_frac + eff_gm * gm_frac
    eff_error = (((eff_ge + eff_gm) * gm / (ge + gm)**2)**2 * ge_error**2 + 
                 ((eff_ge + eff_gm) * ge / (ge + gm)**2)**2 * gm_error**2 + 
                 ge_frac**2 * (eff_ge * (1 - eff_ge) / (mc[ge_mc_num][1]['events'])**0.5)**2 + 
                 gm_frac**2 * (eff_gm * (1 - eff_gm) / (mc[gm_mc_num][1]['events'])**0.5)**2 )**0.5
    # eff = eff_gm     
    # eff_error = (eff_gm * (1 - eff_gm) / (mc[gm_mc_num][1]['events']))**0.5
    return eff * eff_scale[0], (eff_error**2 + eff_scale[1]**2)**0.5


res = []
for elabel, xsec in vis_xsec_data.items():
    # if xsec['nominal_energy'] < 950 or xsec['season'][-4:] == '2017':
        # continue
    ge, ge_error, gm, gm_error = 1.44, 0.0, 1, 0.0
    if int(elabel[:3]) > 950:
        try:
            ge, ge_error, gm, gm_error = load_MC_info(elabel)
        except Exception as e:
            # print(elabel, ":", e)
            pass
        
    try:    
        eff, eff_err = eval_eff(elabel, ge, ge_error, gm, gm_error, eff_scale)
        if elabel == '938.3_109615':
            eff, eff_err = 0.177 * eff_scale[0], 0.00265
        xsection, xsection_err = xsec["visible cross section"], xsec["visible cross section error"]
        res.append(
            (
                xsec['season'], 
                xsec['energy'], 
                round(xsec["visible cross section"] / eff, 4), 
                round(((xsection_err / eff)**2 + (xsection * eff_err / eff**2)**2)**0.5, 4),
                round(eff, 4), 
                round(eff_err, 5)
            )
        )
        xsec["cross section"] = round(xsec["visible cross section"] / eff, 4)
        xsec["cross section error"] = round(((xsection_err / eff)**2 + (xsection * eff_err / eff**2)**2)**0.5, 4)
    except KeyError as e:
        print(elabel, ":", e)

res.sort(key=lambda x: x[0])

seasons = dict()
for season, energy, xsection, xsection_err, eff, eff_err in res:
    if season not in seasons.keys():
        seasons[season] = {'energy' : [], 'xsec' : [], 'xsec_error' : [], 'eff' : [], 'eff_error' : []}
    seasons[season]['energy'].append(str(energy))
    seasons[season]['xsec'].append(str(xsection))
    seasons[season]['xsec_error'].append(str(xsection_err))
    seasons[season]['eff'].append(str(eff))
    seasons[season]['eff_error'].append(str(eff_err))


for season, vals in seasons.items():
    vals['name'] = f'NNbar{season[-4:]}' if season[-4:] == '2022' else season
    vals['energy'] = f"std::vector<double> energy_{vals['name']}" + " = {" + ', '.join(vals['energy']) + '}; // MeV'
    vals['val'] = f"std::vector<double> xsec_{vals['name']}" + " = {" + ', '.join(vals['xsec']) + '}; // nb'
    vals['val_err'] = f"std::vector<double> xsec_err_{vals['name']}" + " = {" + ', '.join(vals['xsec_error']) + '}; // nb'
season_list = [vals for _, vals in seasons.items()]

def render(template_filename, output_filename, **data):
    with open(template_filename) as file_:
        template = jinja2.Template(file_.read()) # type: ignore
    rendered_content = template.render(**data)
    with open(output_filename, "w") as file:
        file.write(rendered_content)

with open(results_data, "w") as file:
    json.dump(dict(sorted(vis_xsec_data.items(), key=lambda record: record[1]['energy'])), file, indent=4)
    
template_filename = pathlib.Path(templates, 'smth_vs_energy.cpp.jinja')

output_filename = pathlib.Path(root_folder, f'graph_drawing_scripts/xsec_{type}.cpp')

render(template_filename, output_filename, seasons = season_list, script_name = f'xsec_{type}', val_name = 'xsec', 
        title = 'e^{+}e^{-} #rightarrow p#bar{p} ' + type_name_official + ' events', y_axis_title = '#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb')
print(output_filename.as_posix())

eff_output_filename = pathlib.Path(root_folder, f'graph_drawing_scripts/eff_{type}.cpp')

for vals in season_list:
    vals['val'] = f"std::vector<double> eff_{vals['name']}" + " = {" + ', '.join(vals['eff']) + '};'
    vals['val_err'] = f"std::vector<double> eff_err_{vals['name']}" + " = {" + ', '.join(vals['eff_error']) + '};'
print(eff_output_filename.as_posix())
render(template_filename, eff_output_filename, seasons = season_list, script_name = f'eff_{type}', val_name = 'eff', 
        title = 'Efficiency for e^{+}e^{-} #rightarrow p#bar{p} ' + type_name_official + ' events', y_axis_title = '#varepsilon, nb')
