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
    max_z: float = 6
    max_track_rho: float = 0.2

class Select_collinear_track_eff:            
    def __init__(self, prelim_file: os.PathLike, filename_pattern: str, select_config: Select_config = Select_config(), is_MC: bool = False):
        self.config = select_config
        raw_file = PurePath(prelim_file)
        matched = re.fullmatch(filename_pattern, raw_file.name)
        self.season = f'season{matched.group(1)}' if matched is not None else 'error_during_matching'
        self.energy_point = str(matched.group(2)) if matched is not None else 'error_during_matching'
        self.season_num = int(matched.group(1)) if matched is not None else 0
        self.energy_point_num = float(matched.group(2)) if matched is not None else 0.
        prelim_tree_cols = ['event_id', 'energy', 'run',
                            'tot_neutral_cal_deposition', 'tot_cal_deposition',
                            'proton_hits', 'proton_dedx', 'proton_z', 'proton_cal_deposition', 'proton_rho',
                            'proton_phi', 'proton_theta', 'proton_mom',
                            'proton_phi_v', 'proton_theta_v', 'proton_mom_v',
                            
                            'antiproton_hits', 'antiproton_dedx', 'antiproton_z', 'antiproton_cal_deposition', 'antiproton_rho',
                            'antiproton_phi', 'antiproton_theta', 'antiproton_mom',
                            'antiproton_phi_v', 'antiproton_theta_v', 'antiproton_mom_v']
        tree_cols_aliases = dict({'event_id' : 'evnum', 'energy' : 'emeas', 'run' : 'runnum',
                                'tot_neutral_cal_deposition' : 'ecalneu', 'tot_cal_deposition' : 'ecaltot',
                                
                                'proton_hits' : 'proton_tnhit', 'proton_dedx' : 'proton_tdedx', 'proton_z' : 'proton_tz',
                                'proton_rho' : 'proton_trho', 'proton_cal_deposition' : 'proton_ten', 
                                'proton_phi' : 'proton_tphi', 'proton_theta' : 'proton_tth', 'proton_mom' : 'proton_tptot',
                                'proton_phi_v' : 'proton_tphiv', 'proton_theta_v' : 'proton_tthv', 'proton_mom_v' : 'proton_tptotv',
                                
                                'antiproton_hits' : 'antiproton_tnhit', 'antiproton_dedx' : 'antiproton_tdedx', 'antiproton_z' : 'antiproton_tz',
                                'antiproton_rho' : 'antiproton_trho', 'antiproton_cal_deposition' : 'antiproton_ten', 
                                'antiproton_phi' : 'antiproton_tphi', 'antiproton_theta' : 'antiproton_tth', 'antiproton_mom' : 'antiproton_tptot',
                                'antiproton_phi_v' : 'antiproton_tphiv', 'antiproton_theta_v' : 'antiproton_tthv', 'antiproton_mom_v' : 'antiproton_tptotv',
                                })
            
        with up.open(f'{raw_file}:prelim') as raw_file: # type: ignore
            self.raw: pd.DataFrame = raw_file.arrays(prelim_tree_cols, aliases=tree_cols_aliases, library='pd') # type: ignore
            
        self.preprocess()
        filter_mask = self.filter()
        self.selected = self.raw[filter_mask].reset_index(drop=True)
    
    def preprocess(self):
        self.raw['season'] = self.season_num
        self.raw['energy_point'] = self.energy_point_num
        self.raw['found_both'] = self.raw[['proton_z', 'antiproton_z']].apply(lambda row: len(row['antiproton_z']) > 0 and len(row['proton_z']) > 0, axis=1, result_type='reduce')

    @property
    def selected_entries_num(self)->int:
        return len(self.selected)
    
    def filter(self):
        # z_filter = self.raw['antiproton_z'].apply(lambda z: bool(np.all(np.abs(z) < self.config.max_z)))
        track_rho_filter = self.raw['antiproton_rho'].apply(lambda rho: bool(np.all(np.abs(rho) < self.config.max_track_rho)))
        filter_mask = track_rho_filter
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
        