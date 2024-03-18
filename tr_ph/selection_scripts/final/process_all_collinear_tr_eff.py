from enum import Enum, auto
import pathlib
import re
import json
from multiprocessing.pool import Pool

import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph/')
from config import PrelimRootFilesFolder_Coll_Track_Eff, FinalRootFilesFolder
from select_coll_tr_eff import Select_collinear_track_eff, make_if_not_exists



def select_exp(file: pathlib.Path, pattern: str, info: dict):
    select_coll = Select_collinear_track_eff(file, pattern)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.exp.value, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    print('Is saved?', select_coll.save(pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_tr_eff.root'), True))
    print('Entries after selection =', select_coll.selected_entries_num)
    return

def select_MC(file: pathlib.Path, MC_pattern: str, info: dict, json_key: str | None = None):
    matched = re.search(MC_pattern, file.name)    
    if matched is None:
        print(f"Couldn't match file {file.name}. It was skipped.")
        return None
    Ge = matched.group(3)
    Gm = matched.group(4)
    run_num = 0 # matched.group(5)
    select_coll = Select_collinear_track_eff(file, MC_pattern, is_MC=True)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.MC.value, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    # output_file_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_tr_eff_Ge{Ge}_Ge{Gm}_run000{run_num}.root')
    output_file_path = pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll_tr_eff_Ge{Ge}_Ge{Gm}_FTFP_BERT_HP.root')
    is_saved = select_coll.save(output_file_path, True)
    print(f'Entries after selection in run {json_key} =', select_coll.selected_entries_num)
    print(f'output_file_path = {output_file_path}')
    try:
        info[json_key]['tr_eff processed_file_location'] = output_file_path.as_posix()
    except KeyError as e:
        print(f'Something is wrong with {json_key} in info file: {e}')
    return json_key, info[json_key]

class WorkingMode(Enum):
    EXP = auto()     
    MC = auto()    
     
if __name__ == '__main__':
    # exp
    raw_files_exp = [x for x in PrelimRootFilesFolder_Coll_Track_Eff.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
    exp_pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))_coll_track_efficiency_prelim.root'
    exp_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/exp_info.json'
    # MC
    raw_files_MC = [x for x in PrelimRootFilesFolder_Coll_Track_Eff.MC.value.iterdir() if x.is_file() and x.suffix == '.root']
    raw_files_MC = [x for x in pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/prelim/FTFP_BERT_HP/collinear_track_efficiency').iterdir() if x.is_file() and x.suffix == '.root']
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)_coll_track_efficiency_run000(\d+)_prelim.root'
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)'
    MC_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/MC_info.json'
    
    # Set working mode
    mode = WorkingMode.MC
    
    select = select_MC if mode is WorkingMode.MC else select_exp
    raw_files = raw_files_MC if mode is WorkingMode.MC else raw_files_exp
    info_filename = MC_info_filename if mode is WorkingMode.MC else exp_info_filename
    with open(info_filename) as file:
        info = json.load(file) 

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
    
    select_params = [(file, MC_pattern if mode is WorkingMode.MC else exp_pattern, info, get_json_key(file.name)) for file in raw_files]
    def progress(res):
        print(f"Done:{len(res)} out of {len(select_params)}")
        
    # with Pool(4) as pool:
        # res = pool.starmap(select, select_params)
    res = []
    for pars in select_params:
        res.append(select(*pars))
    if all([x is not None for x in res]):    
        res = dict(res) # type: ignore
        for key, val in res.items():
            info[key] = val
    with open(info_filename, 'w') as file:
        json.dump(info, file, indent=4) 
        