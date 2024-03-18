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
    output_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll.root')
    print('Is saved?', select_coll.save(output_path, True))
    print('Entries after selection =', select_coll.selected_entries_num)
    return 'selected_entries', select_coll.selected_entries_num

def select_MC(file: pathlib.Path, MC_pattern: str, info: dict, json_key: str | None = None):
    matched = re.search(MC_pattern, file.name)
    if matched is None:
        print(f"Couldn't match file {file.name}. It was skipped.")
        return None
    Ge = matched.group(3)
    Gm = matched.group(4)
    run_num = 0 # matched.group(5)
    select_coll = Select_collinear(file, MC_pattern, is_MC=True)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.MC.value, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    # output_file_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_Ge{Ge}_Ge{Gm}_run000{run_num}.root')
    output_file_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_Ge{Ge}_Ge{Gm}_FTFP_BERT_HP.root')
    is_saved = select_coll.save(output_file_path, True)
    print(f'Entries after selection in run {json_key} =', select_coll.selected_entries_num)
    print(f'output_file_path = {output_file_path}')
    try:
        info[json_key]['selected_events'] = select_coll.selected_entries_num
        info[json_key]['eff'] = select_coll.selected_entries_num / info[json_key]['events']
        info[json_key]['processed_file_location'] = output_file_path.as_posix()
    except KeyError as e:
        print(f'Something is wrong with run000{run_num} in info file: {e}')
    return json_key, info[json_key]

class WorkingMode(Enum):
    EXP = auto()     
    MC = auto()    
     
if __name__ == '__main__':
    # exp
    raw_files_exp = [x for x in PrelimRootFilesFolder_Coll.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
    exp_pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))_coll_prelim.root'
    exp_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/exp_info.json'
    # MC
    raw_files_MC = [x for x in PrelimRootFilesFolder_Coll.MC.value.iterdir() if x.is_file() and x.suffix == '.root']
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)_coll_run000(\d+)_prelim.root'
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)'

    MC_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/MC_info.json'
    
    # Set working mode
    mode = WorkingMode.MC
    
    select = select_MC if mode is WorkingMode.MC else select_exp
    raw_files = raw_files_MC if mode is WorkingMode.MC else raw_files_exp
    info_filename = MC_info_filename if mode is WorkingMode.MC else exp_info_filename
    def get_json_key(filename: str):
        pattern_string =  r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)'
        matched = re.search(pattern_string, filename)
        if matched is None:
            print('sear')
            return None
        season = matched.group(1)
        energy = matched.group(2)
        Ge = matched.group(3)
        Gm = matched.group(4)

        for run, run_data in info.items():
            if int(run_data['season'][-4:]) == int(season) and run_data["Ge^2"] == int(Ge) and run_data["Gm^2"] == int(Gm) and \
                abs(run_data['E_beam'] - float(energy)) < 0.1 and run_data['Physics list'] == 'FTFP_BERT_HP':
                return run
        return None
    
    with open(info_filename) as file:
        info = json.load(file) 
        
    select_params = [(file, MC_pattern if mode is WorkingMode.MC else exp_pattern, info, get_json_key(file.name)) for file in raw_files if get_json_key(file.name) is not None]
    
    def progress(res):
        print(f"Done:{len(res)} out of {len(select_params)}")
        
    with Pool(6) as pool:
        res = pool.starmap(select, select_params)
    res = list(filter(lambda x: x is not None, res))
    if all([x is not None for x in res]):    
        res = dict(res) # type: ignore
        for key, val in res.items():
            info[key] = val
    with open(info_filename, 'w') as file:
        json.dump(info, file, indent=4) 
        