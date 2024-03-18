from math import pi
import os
from pathlib import PurePath
import warnings
from attr import dataclass
import re
import uproot as up
import pandas as pd
import numpy as np

import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph/')
from config import final_tree_name


def make_if_not_exists(path: os.PathLike):
    if not os.path.isdir(path):
        os.mkdir(path)
            
@dataclass
class Select_config:
    max_delta_phi: float = 0.15
    max_delta_theta: float = 0.2
    max_z: float = 8
    max_track_rho: float = 0.2
    max_mom_ratio: float = 0.1

class Select_collinear:            
    def __init__(self, prelim_file: os.PathLike, filename_pattern: str, select_config: Select_config = Select_config(), is_MC: bool = False):
        self.config = select_config
        raw_file = PurePath(prelim_file)
        matched = re.search(filename_pattern, raw_file.name)
        self.season = f'season{matched.group(1)}' if matched is not None else 'error_during_matching'
        self.energy_point = str(matched.group(2)) if matched is not None else 'error_during_matching'
        self.season_num = int(matched.group(1)) if matched is not None else 0
        self.energy_point_num = float(matched.group(2)) if matched is not None else 0.
        prelim_tree_cols = ['event_id', 'energy', 'run', 'nt',
                            'tot_neutral_cal_deposition', 'tot_cal_deposition',
                            'hits', 'dedx', 'z', 'charge', 'cal_deposition', 'rho',
                            'phi', 'theta', 'mom',
                            'phi_v', 'theta_v', 'mom_v']
        tree_cols_aliases = dict({'event_id' : 'evnum', 'energy' : 'emeas', 'run' : 'runnum',
                                'tot_neutral_cal_deposition' : 'ecalneu', 'tot_cal_deposition' : 'ecaltot',
                                    'hits' : 'tnhit', 'dedx' : 'tdedx', 'z' : 'tz', 'rho' : 'trho',
                                'charge' : 'tcharge', 'cal_deposition' : 'ten', 
                                'phi' : 'tphi', 'theta' : 'tth', 'mom' : 'tptot',
                                'phi_v' : 'tphiv', 'theta_v' : 'tthv', 'mom_v' : 'tptotv',
                                'phi_MC' : 'tphi_MC', 'theta_MC' : 'tth_MC', 'mom_MC' : 'tptot_MC'
                                })
        if is_MC:
            prelim_tree_cols.extend(['phi_MC', 'theta_MC', 'mom_MC'])
            
        with up.open(f'{raw_file}:prelim') as raw_file: # type: ignore
            self.raw: pd.DataFrame = raw_file.arrays(prelim_tree_cols, aliases=tree_cols_aliases, library='pd') # type: ignore
            
        self.preprocess()
        filter_mask = self.filter()
        self.selected = self.raw[filter_mask].reset_index(drop=True)
    
    def preprocess(self):
        self.raw['delta_theta'] = self.raw['theta_v'].apply(lambda x: x[0] + x[1] - pi)
        self.raw['delta_phi'] = self.raw['phi_v'].apply(lambda x: abs(x[0] - x[1]) - pi)
        self.raw['mom_ratio'] = self.raw['mom_v'].apply(lambda x: abs(x[0] - x[1]) / (x[0] + x[1]))
        self.raw['season'] = self.season_num
        self.raw['energy_point'] = self.energy_point_num
        
        # Fake branches.
        self.raw['vrho'] = [-1] * len(self.raw['phi_v'])
        self.raw['proton_index'] = [-1] * len(self.raw['phi_v'])
    
    @property
    def selected_entries_num(self)->int:
        return len(self.selected)
    
    def filter(self):
        delta_phi_filter = np.abs(self.raw['delta_phi']) < self.config.max_delta_phi
        delta_theta_filter = np.abs(self.raw['delta_theta']) < self.config.max_delta_theta
        z_filter = self.raw['z'].apply(lambda rho: bool(np.all(np.abs(rho) < self.config.max_z)))
        track_rho_filter = self.raw['rho'].apply(lambda rho: bool(np.all(np.abs(rho) < self.config.max_track_rho)))
        mom_ratio_filter = self.raw['mom_ratio'] < self.config.max_mom_ratio
        filter_mask = delta_phi_filter & delta_theta_filter & z_filter & track_rho_filter & mom_ratio_filter
        return filter_mask

    def save(self, processed: os.PathLike, recreate: bool) -> bool:
        """save processed and filtered tree

        Parameters
        ----------
        processed : os.PathLike
            path where to save file.
            Method can handle situations where parent_2 doesn't exist but if parent_1 doesn't exist too it will not save.
            .../parent_1/parent_2/filename.root
        recreate : bool
            do you want the method to recreate files?
            
        Returns
        -------
        bool
            Show whether the tree was saved or not.
        """
        selected_file = PurePath(processed)
        if selected_file.suffix != '.root':
            warnings.warn(f'File {selected_file} is not of .root extension.')
            return False
        
        if not os.path.isdir(selected_file.parent):
            warnings.warn(f'Grandparent folder int {selected_file} does not exists.')
            return False
        
        if not recreate and os.path.isfile(selected_file):
            warnings.warn(f'File {selected_file} already exists and recreate option is {recreate}.')
            return False
        
        make_if_not_exists(selected_file.parent)
        with up.recreate(selected_file) as new_file:
            new_file[final_tree_name] = self.selected
        if not os.path.isfile(selected_file):
            warnings.warn(f'File {selected_file} was not saved.')
            return False
        return True 
        