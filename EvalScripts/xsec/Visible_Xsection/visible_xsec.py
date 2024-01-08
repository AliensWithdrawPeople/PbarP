from functools import reduce
from itertools import chain
import json
from pathlib import Path
import uproot as up
import re

import sys
sys.path.append('C:/work/Science/BINP/PbarP/')
from tr_ph.config import FinalRootFilesFolder, lumi, final_tree_name, exp_info_path, collinear_results_data, stars_results_data, templates, root_folder

from Utility import EventType, Patterns, format_data, get_energy_point_value, eval_xsection, get_root_files, get_entries, render


# Return (nominal_energies, energies, xsecs, xsec_errs)
def get_xsection(season_name: str, root_file_pattern: Patterns, event_type: EventType)->tuple[list[float], list[float], list[float], list[float]]:
    with open(lumi) as file:
        lumi_data: dict = json.load(file)
    final_root_files_folder = FinalRootFilesFolder.exp.value
    # Retrieving root files [(energy_point_name, [files])]
    events_files: list[tuple[str, list[Path]]] = [(x.name, get_root_files(x)) for x in final_root_files_folder.iterdir() if x.is_dir() and 'energy' in x.name ]
    res = {}
    for energy_point_name, files in events_files:
        energy_point = get_energy_point_value(energy_point_name)
        for file in files:
            if re.fullmatch(root_file_pattern.value, file.name) is None:
                continue

            with up.open(f'{file}:{final_tree_name}') as events:  # type: ignore
                tree = events.arrays(['vrho', 'proton_index'], library='pd') # type: ignore
                
            entries = get_entries(event_type, tree)
            
            season = file.name.split('_')[0]
            luminosity, luminosity_err = lumi_data[season][str(energy_point)][1]
            mean_energy, mean_energy_stat_err = lumi_data[season][str(energy_point)][0]
            res[(season, energy_point)] = (mean_energy, *eval_xsection(*entries, luminosity, luminosity_err))


    res_filtered = dict(filter(lambda item: item[0][0] == season_name, res.items()))

    xsec = [val[1] for _, val in res_filtered.items()]
    xsec_err = [val[2] for _, val in res_filtered.items()]
    energy = [val[0] for _, val in res_filtered.items()]
    nominal_energy = [key[1] for key, _ in res_filtered.items()]
    return nominal_energy, energy, xsec, xsec_err

 
# Configuration Starts
ev_type = "coll"
if ev_type == "coll":
    event_type = EventType.collinear
    root_file_pattern = Patterns.coll_final_root_file_pattern
    seasons = ['season2017', 'season2019', 'season2020', 'season2021', 'season2022']
    template_filename = Path(templates, 'vis_xsec_coll.cpp.jinja')
    output_filename = Path(root_folder, 'graph_drawing_scripts/vis_xsec_coll.cpp')
    results_data = collinear_results_data
else:
    event_type = EventType.annihilation
    root_file_pattern = Patterns.stars_final_root_file_pattern
    seasons = ['season2017', 'season2019', 'season2020', 'season2021', 'season2022']
    template_filename = Path(templates, 'vis_xsec_stars.cpp.jinja')
    output_filename = Path(root_folder, 'graph_drawing_scripts/vis_xsec_stars.cpp')
    results_data = stars_results_data
# Configuration Ends

seasons_data = []
results = []
aux_curly_bracket= ('{', '}')
for season in seasons:
    nominal_energy, energy, xsec, xsec_err = get_xsection(season, root_file_pattern, event_type) # type: ignore
    results.append({
        "season" : season,
        "nominal_energy" : nominal_energy,
        "energy" : energy,
        "xsec" : xsec,
        "xsec_error" : xsec_err,
    })
    
    name = f'// {season}'
    nominal_energy = f'std::vector<double> nominal_energy_{season} ={aux_curly_bracket[0]}' + ', '.join([str(val) for val in nominal_energy]) + f'{aux_curly_bracket[1]}; // MeV'
    energy = f'std::vector<double> energy_{season} ={aux_curly_bracket[0]}' + ', '.join([str(val) for val in energy]) + f'{aux_curly_bracket[1]}; // MeV'
    xsec = f'std::vector<double> xsec_{season} = {aux_curly_bracket[0]}' + ', '.join([str(val) for val in xsec]) + f'{aux_curly_bracket[1]}; // nb'
    xsec_error = f'std::vector<double> xsec_err_{season} = {aux_curly_bracket[0]}' + ', '.join([str(val) for val in xsec_err]) + f'{aux_curly_bracket[1]}; // nb\n'

    seasons_data.append({
        "name" : name,
        "nominal_energy" : nominal_energy,
        "energy" : energy,
        "xsec" : xsec,
        "xsec_error" : xsec_error,
    })


render(data = seasons_data, template_filename = template_filename, output_filename = output_filename)

results = [format_data(data, exp_info_path) for data in results]
formatted = reduce(lambda acc, val: dict(chain(acc.items(), val.items())), results, dict())

with open(results_data, 'w') as f:
    json.dump(formatted, f, indent = 4)
    