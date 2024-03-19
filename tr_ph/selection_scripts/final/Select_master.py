from enum import Enum, member, auto
from pathlib import Path
import re
import json
from multiprocessing.pool import Pool
import os

import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph/')
from config import FinalRootFilesFolder
from select_coll import Select_collinear
from select_stars import Select_stars
from select_coll_tr_eff import Select_collinear_track_eff


def make_if_not_exists(path: os.PathLike):
    if not os.path.isdir(path):
        os.mkdir(path)
            
class WorkingMode(Enum):
    EXP = auto()     
    MC = auto()    

class EventType(Enum):
    coll = member(Select_collinear)
    stars = member(Select_stars)
    coll_tr_eff = member(Select_collinear_track_eff)
    
class Select_master:
    exp_pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))'
    MC_pattern = r'season(\d+)_e([-+]?(?:\d*\.*\d+))_Ge(\d+)_Gm(\d+)'
    exp_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/exp_info.json'
    MC_info_filename = 'C:/work/Science/BINP/PbarP/tr_ph/MC_info.json'
    
    def __init__(self, prelim_files_folder: Path, event_type: EventType, working_mode: WorkingMode, phys_list: str = 'FTFP_BERT'):
        self.raw_files = [x for x in prelim_files_folder.iterdir() if x.is_file() and x.suffix == '.root']
        self.event_type = event_type
        self.working_mode = working_mode
        self.phys_list = phys_list
        if self.working_mode is WorkingMode.MC:
            self.info_filename = self.MC_info_filename
            self.get_json_key = self.get_json_key_MC
            self.pattern_string = self.MC_pattern
        if self.working_mode is WorkingMode.EXP:
            self.info_filename = self.exp_info_filename
            self.get_json_key = self.get_json_key_EXP
            self.pattern_string = self.exp_pattern
            
    def execute(self):
        info_filename = self.MC_info_filename if self.working_mode is WorkingMode.MC else self.exp_info_filename
        get_json_key = self.get_json_key_MC if self.working_mode is WorkingMode.MC else self.get_json_key_EXP
        
        with open(info_filename) as file:
            info = json.load(file) 
            
        select_params = [(file, self.pattern_string, info, json_key) for file in self.raw_files if (json_key := get_json_key(file.name, info, self.phys_list)) is not None]
        self.select(*select_params[-1])
        # with Pool(6) as pool:
        #     res = pool.starmap(self.select, select_params)
        # res = list(filter(lambda x: x is not None, res))
        # if all([x is not None for x in res]):    
        #     res = dict(res) # type: ignore
        #     for key, val in res.items():
        #         info[key] = val
        # with open(info_filename, 'w') as file:
        #     json.dump(info, file, indent=4) 
    
    def select(self, file: Path, pattern: str, info: dict, json_key: str):
        selector = self.event_type.value(file, pattern, is_MC=(self.working_mode is WorkingMode.MC))
        energy_point_folder = Path(FinalRootFilesFolder.exp.value, f'energy_{selector.energy_point}MeV')
        make_if_not_exists(energy_point_folder)
        output_fname = self.make_output_filename(self.working_mode, file.name, selector.season, json_key)
        if output_fname is None:
            return
        output_file_path = Path(energy_point_folder, output_fname)
        print('Is saved?', selector.save(output_file_path, True, make_if_not_exists))
        print('Entries after selection =', selector.selected_entries_num)
        print("Output file's path =", output_file_path.as_posix())
        try:
            if self.working_mode is WorkingMode.MC:
                info[json_key][f'selected_events_{self.event_type.name}'] = selector.selected_entries_num
                info[json_key][f'eff_{self.event_type.name}'] = selector.selected_entries_num / info[json_key]['events']
                info[json_key][f'processed_file_location_{self.event_type.name}'] = output_file_path.as_posix()
            
            if self.working_mode is WorkingMode.EXP:
                info[json_key][f'selected_entries_{self.event_type.name}'] = selector.selected_entries_num
                
        except KeyError as e:
            print(f'Something is wrong with {json_key} in info file (working_mode = {self.working_mode.name}): {e}')
        return json_key, info[json_key]


    def make_output_filename(self, mode, filename: str, season: str, json_key: str):
        if mode is WorkingMode.EXP:
            return f'{season}_{self.event_type.name}.root'
        matched = re.search(self.MC_pattern, filename)
        if matched is None:
            print(f"Couldn't match file {filename}. It was skipped.")
            return None
        Ge = matched.group(3)
        Gm = matched.group(4)
        return f'{season}_{self.event_type.name}_Ge{Ge}_Ge{Gm}_{json_key}.root'
        
    @classmethod
    def get_json_key_MC(cls, filename: str, info, phys_list: str = 'FTFP_BERT'):
        pattern_string = cls.MC_pattern
        matched = re.search(pattern_string, filename)
        if matched is None:
            return None
        season = matched.group(1)
        energy = matched.group(2)
        Ge = matched.group(3)
        Gm = matched.group(4)

        for run, run_data in info.items():
            if int(run_data['season'][-4:]) == int(season) and run_data["Ge^2"] == int(Ge) and run_data["Gm^2"] == int(Gm) and \
                abs(run_data['E_beam'] - float(energy)) < 0.1 and run_data['Physics list'] == phys_list:
                return run
        return None
    
    @classmethod
    def get_json_key_EXP(cls, filename: str, info, phys_list: str = ''):
        pattern_string =  cls.exp_pattern
        matched = re.search(pattern_string, filename)
        if matched is None:
            print('Search failed')
            return None
        season = matched.group(1)
        energy = matched.group(2)

        for key, data in info.items():
            if int(data['season'][-4:]) == int(season) and abs(float(key.split('_')[0]) - float(energy)) < 0.1:
                return key
        print(energy, ':', season)
        return None
