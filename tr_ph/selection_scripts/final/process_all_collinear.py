from enum import Enum, auto
import pathlib
import re
import json
from multiprocessing.pool import Pool

import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph/')
from config import PrelimRootFilesFolder_Coll, FinalRootFilesFolder
from select_coll import Select_collinear, make_if_not_exists



def select_exp(file: pathlib.Path, pattern: str, info: dict):
    select_coll = Select_collinear(file, pattern)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.exp.value, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    select_coll.save(pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll.root'), True)
    print('Entries after selection =', select_coll.selected_entries_num)
    return '', {}

def select_MC(file: pathlib.Path, MC_pattern: str, info: dict):
    matched = re.fullmatch(MC_pattern, file.name)
    if matched is None:
        print(f"Couldn't match file {file.name}. It was skipped.")
        return None
    Ge = matched.group(3)
    Gm = matched.group(4)
    run_num = matched.group(5)
    select_coll = Select_collinear(file, MC_pattern, is_MC=True)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.MC.value, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    output_file_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_Ge{Ge}_Ge{Gm}_run000{run_num}.root')
    is_saved = select_coll.save(output_file_path, True)
    print(f'Entries after selection in run run000{run_num} =', select_coll.selected_entries_num)
    try:
        info[f'run000{run_num}']['selected_events'] = select_coll.selected_entries_num
        info[f'run000{run_num}']['eff'] = select_coll.selected_entries_num / info[f'run000{run_num}']['events']
        info[f'run000{run_num}']['processed_file_location'] = output_file_path.as_posix()
    except KeyError as e:
        print(f'Something is wrong with run000{run_num} in info file: {e}')
    return f'run000{run_num}', info[f'run000{run_num}']

class WorkingMode(Enum):
    EXP = auto()     
    MC = auto()    
     
if __name__ == '__main__':
    # exp
    raw_files = [x for x in PrelimRootFilesFolder_Coll.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
    exp_pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))_coll_prelim.root'
    exp_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/exp_info.json'
    # MC
    raw_files = [x for x in PrelimRootFilesFolder_Coll.MC.value.iterdir() if x.is_file() and x.suffix == '.root']
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)_coll_run000(\d+)_prelim.root'
    MC_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/MC_info.json'
    
    # Set working mode
    mode = WorkingMode.MC
    
    select = select_MC if mode is WorkingMode.MC else select_exp
    info_filename = MC_info_filename if mode is WorkingMode.MC else exp_info_filename
    with open(info_filename) as file:
        info = json.load(file) 
    
    select_params = [(file, MC_pattern if mode is WorkingMode.MC else exp_pattern, info) for file in raw_files]
    with Pool(4) as pool:
        res = pool.starmap(select, select_params)
    res = list(filter(lambda x: x is not None, res))
    if all([x is not None for x in res]):    
        res = dict(res) # type: ignore
        for key, val in res.items():
            info[key] = val
    with open(info_filename, 'w') as file:
        json.dump(info, file, indent=4) 
        