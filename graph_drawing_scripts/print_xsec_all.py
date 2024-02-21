import jinja2
import json
import pathlib
import copy

import numpy as np
import pandas as pd

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, collinear_results_data, stars_results_data, GeGm_Fit_Result_json, templates, root_folder
from tr_ph.EnergyPointData.EnergyPoints import get_energy_points

points = get_energy_points()

results_data = collinear_results_data if type == "coll" else stars_results_data
GeGm = json.loads(GeGm_Fit_Result_json.read_text())
MC_info = json.loads(MC_info_path.read_text())
vis_xsec_data_coll = json.loads(collinear_results_data.read_text())
vis_xsec_data_stars = json.loads(stars_results_data.read_text())



tmp = {'energy' : [], 'xsec' : [], 'xsec_error' : [], 'eff' : [], 'eff_error' : []}
seasons: dict[str, dict[str, list[str]]] = {'HIGH2017' : copy.deepcopy(tmp), 'HIGH2019' : copy.deepcopy(tmp), 'HIGH2020' : copy.deepcopy(tmp), 'HIGH2021' : copy.deepcopy(tmp), 'HIGH2022' : copy.deepcopy(tmp)}
total = {'energy' : [], 'xsec' : [], 'xsec_error' : [], 'energy_spread' : []}
for elabel, vals in vis_xsec_data_stars.items():
    if vals['energy'] > 955 or 'cross section' not in vals.keys():
        continue
    seasons[vals['season']]['energy'].append(str(vals['energy']))
    seasons[vals['season']]['xsec'].append(str(vals['cross section']))
    seasons[vals['season']]['xsec_error'].append(str(vals['cross section error']))
    
    total['energy'].append(str(vals['energy']))
    total['xsec'].append(str(vals['cross section']))
    total['xsec_error'].append(str(vals['cross section error'] + (0.02 if vals['energy'] < 938.2 else 0)))
    total['energy_spread'].append(str(points[points['elabel'] == elabel]['mean_spread'].values[-1]))

for elabel, vals in vis_xsec_data_coll.items():
    if vals['energy'] < 955 or 'cross section' not in vals.keys():
        continue
    seasons[vals['season']]['energy'].append(str(vals['energy']))
    seasons[vals['season']]['xsec'].append(str(vals['cross section']))
    seasons[vals['season']]['xsec_error'].append(str(vals['cross section error']))
        
    total['energy'].append(str(vals['energy']))
    total['xsec'].append(str(vals['cross section']))
    total['xsec_error'].append(str(vals['cross section error']))
    total['energy_spread'].append(str(points[points['elabel'] == elabel]['mean_spread'].values[-1]))


for season, vals in seasons.items():
    vals['name'] = f'NNbar{season[-4:]}' if season[-4:] == '2022' else season # type: ignore
    vals['energy'] = f"std::vector<double> energy_{vals['name']}" + " = {" + ', '.join(vals['energy']) + '}; // MeV'  # type: ignore
    vals['val'] = f"std::vector<double> xsec_{vals['name']}" + " = {" + ', '.join(vals['xsec']) + '}; // nb'  # type: ignore
    vals['val_err'] = f"std::vector<double> xsec_err_{vals['name']}" + " = {" + ', '.join(vals['xsec_error']) + '}; // nb'  # type: ignore
season_list = [vals for _, vals in seasons.items()]

def render(template_filename, output_filename, **data):
    with open(template_filename) as file_:
        template = jinja2.Template(file_.read()) # type: ignore
    rendered_content = template.render(**data)
    with open(output_filename, "w") as file:
        file.write(rendered_content)
    
template_filename = pathlib.Path(templates, 'smth_vs_energy.cpp.jinja')

output_filename = pathlib.Path(root_folder, f'graph_drawing_scripts/tot_sigma_vs_E_by_seasons.cpp')
print(output_filename.as_posix())
render(template_filename, output_filename, seasons = season_list, script_name = f'tot_sigma_vs_E_by_seasons', val_name = 'xsec', 
        title = 'e^{+}e^{-} #rightarrow p#bar{p} both types of events', y_axis_title = '#sigma_{e^{+}e^{-} #rightarrow p#bar{p}}, nb')

energy = "{" + ', '.join(total['energy']) + "}"
xsec = "{" + ','.join(total['xsec']) + "}"
xsec_err = "{" + ', '.join(total['xsec_error']) + "}"
energy_spread = "{" + ', '.join(total['energy_spread']) + "}"

template_filename = pathlib.Path(templates, 'tot_sigma_vs_energy.cpp.jinja')
output_filename = pathlib.Path(root_folder, f'graph_drawing_scripts/tot_sigma_vs_E.cpp')
print(output_filename.as_posix())
render(template_filename, output_filename, 
       energy=energy,
       xsec=xsec,
       xsec_err=xsec_err,
       energy_spread=energy_spread
       )
