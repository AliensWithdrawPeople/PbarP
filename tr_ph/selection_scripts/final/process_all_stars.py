from enum import Enum, auto
import json
from multiprocessing import Pool
import re
import pathlib

from select_stars import Select_stars, make_if_not_exists, Select_config_stars
from config import PrelimRootFilesFolder_Stars, FinalRootFilesFolder



# raw_files = [x for x in PrelimRootFilesFolder_Stars.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
# raw_files = [pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e970_stars_prelim.root'),
#              pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e980_stars_prelim.root'),
#              pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e990_stars_prelim.root'),
#              pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e1003.5_stars_prelim.root')]

# raw_files = [pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2022_e937.5_stars_prelim.root')]

# for file in raw_files:
#     select_stars = Select_stars(file)
#     energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.exp.value, f'energy_{select_stars.energy_point}MeV')
#     make_if_not_exists(energy_point_folder)
#     select_stars.save(pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars_bkg.root'), True)
    
    
    
def select_exp(file: pathlib.Path, pattern: str, info: dict):
    select_stars = Select_stars(file, pattern)    
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.exp.value, f'energy_{select_stars.energy_point}MeV')
    
    make_if_not_exists(energy_point_folder)
    print('Is saved?', select_stars.save(pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars.root'), True))
    print('Entries after selection =', select_stars.get_selected_entries_num())
    return

def select_MC(file: pathlib.Path, MC_pattern: str, info: dict, json_key: str | None = None):
    matched = re.search(MC_pattern, file.name)
    if matched is None:
        print(f"Couldn't match file {file.name}. It was skipped.")
        return None
    Ge = matched.group(3)
    Gm = matched.group(4)
    run_num = 0 # matched.group(5)
    select_stars = Select_stars(file, MC_pattern)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.MC.value, f'energy_{select_stars.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    # output_file_path = pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars_Ge{Ge}_Ge{Gm}_run000{run_num}.root')
    output_file_path = pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars_Ge{Ge}_Ge{Gm}_FTFP_BERT_HP.root')
    is_saved = select_stars.save(output_file_path, True)
    print(f'Entries after selection in run {json_key} =', select_stars.get_selected_entries_num())
    print(f'output_file_path = {output_file_path}')

    try:
        info[json_key]['selected_events_stars'] = select_stars.get_selected_entries_num()
        info[json_key]['eff_stars'] = select_stars.get_selected_entries_num() / info[json_key]['events']
        info[json_key]['processed_file_location_stars'] = output_file_path.as_posix()
    except KeyError as e:
        print(f'Something is wrong with {json_key} in info file: {e}')
    return json_key, info[json_key]



class WorkingMode(Enum):
    EXP = auto()     
    MC = auto()    
     
if __name__ == '__main__':
    # exp
    raw_files_exp = [x for x in PrelimRootFilesFolder_Stars.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
    exp_pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))_stars_prelim.root'
    exp_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/exp_info.json'
    # MC
    raw_files_MC = [x for x in PrelimRootFilesFolder_Stars.MC.value.iterdir() if x.is_file() and x.suffix == '.root']
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)_stars_run000(\d+)_prelim.root'
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

    select_params = [(file, MC_pattern if mode is WorkingMode.MC else exp_pattern, info, get_json_key(file.name)) for file in raw_files]
    
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
        