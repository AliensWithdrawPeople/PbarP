import json
from pathlib import Path
import uproot as up
import re

import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph')
from config import final_root_files_folder, lumi, final_tree_name

from Utility import EventType, Patterns, get_energy_point_value, eval_xsection, get_root_files, get_entries


# Return (energies, xsecs, xsec_errs)
def get_xsection(season_name: str, root_file_pattern: Patterns, event_type: EventType)->tuple[list[float], list[float], list[float]]:
    with open(lumi) as file:
        lumi_data: dict = json.load(file)

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
    return energy, xsec, xsec_err

 
# Configuration 
event_type = EventType.bkg_annihilation
root_file_pattern = Patterns.bkg_stars_final_root_file_pattern
seasons = ['season2017', 'season2019', 'season2020', 'season2021', 'season2022']

# Print for all seasons
aux_curly_bracket= ('{', '}')
for season in seasons:
    energy, xsec, xsec_err = get_xsection(season, root_file_pattern, event_type) # type: ignore
    print(f'// {season}')
    print(f'std::vector<double> energy_{season} ={aux_curly_bracket[0]}', ', '.join([str(val) for val in energy]), f'{aux_curly_bracket[1]}; // MeV')
    print(f'std::vector<double> xsec_{season} = {aux_curly_bracket[0]}', ', '.join([str(val) for val in xsec]), f'{aux_curly_bracket[1]}; // nb')
    print(f'std::vector<double> xsec_err_{season} = {aux_curly_bracket[0]}', ', '.join([str(val) for val in xsec_err]), f'{aux_curly_bracket[1]}; // nb\n')

# for season in seasons:
#     energy, xsec, xsec_err = get_xsection('season2019', root_file_pattern, event_type) # type: ignore
#     print(f"-------------------- {season} -------------------")
#     print('energy =', energy, '# MeV')
#     print('xsection =', xsec, '# nb')
#     print('xsection_error =', xsec_err, '# nb')
