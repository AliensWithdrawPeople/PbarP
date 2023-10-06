import os
from pathlib import PurePath
import warnings
from attr import dataclass
import re
import uproot as up
import pandas as pd
import numpy as np
import itertools

import sys
# caution: path[0] is reserved for script path (or '' in REPL)
sys.path.insert(1, 'C:/work/Science/BINP/PbarP/tr_ph')
from config import final_tree_name


def make_if_not_exists(path: os.PathLike):
    if not os.path.isdir(path):
        os.mkdir(path)
            
@dataclass
class Select_config_stars:
    max_delta_phi: float = 0.15 # rad
    max_delta_theta: float = 0.2 # rad
    max_z: float = 8 # cm
    max_vertex_z: float = 8 # cm
    vertex_track_number_filter: float = 3
        
    max_vertex_rho: float = 2.5 # cm
    min_vertex_rho: float = 1.2 # cm
    
    vertex_track_min_rho: float = 0.15 # cm
    max_sigma_t0: float = 10 # ns
    
    # tot_cal_depo_filter > tot_cal_depo_filter_slope * p_max + tot_cal_depo_filter_const
    tot_cal_depo_filter_slope: float = -2
    tot_cal_depo_filter_const: float = 600 # MeV
    min_tot_cal_depo: float = 500 # MeV
    min_p_max: float = 150 # MeV
    max_p_max: float = 1000 # MeV
    min_p_min: float = 50 # MeV
    
    min_delta_phi: float = 0.03 # rad
    min_delta_theta: float = 0.03 # rad
    

class Select_stars:            
    def __init__(self, prelim_file: os.PathLike, select_config: Select_config_stars = Select_config_stars()):
        self.config = select_config
        raw_file = PurePath(prelim_file)
        pattern = r'scan(\d+)_e([-+]?(?:\d*\.*\d+))_stars_prelim.root'
        matched = re.fullmatch(pattern, raw_file.name)
        self.season = f'season{matched.group(1)}' if matched is not None else 'error_during_matching'
        self.energy_point = str(matched.group(2)) if matched is not None else 'error_during_matching'
        self.season_num = int(matched.group(1)) if matched is not None else 0
        self.energy_point_num = float(matched.group(2)) if matched is not None else 0.
        
        with up.open(f'{raw_file}:prelim') as raw_file: # type: ignore
            self.raw: pd.DataFrame = raw_file.arrays(['event_id', 'energy', 'run', 'nt', 'min_rho', 'trigger', # type: ignore
                                            'vrho', 'vz', 'is_coll', 'proton_index', 'vtrk',
                                            'tot_neutral_cal_deposition', 'tot_cal_deposition',
                                            'hits', 'dedx', 'z', 'charge', 'cal_deposition', 'rho', 't0', 'tant',
                                            'phi', 'theta', 'mom',
                                            'phi_v', 'theta_v', 'mom_v'], 
                                            aliases={'event_id' : 'evnum', 'energy' : 'emeas', 'run' : 'runnum', 'trigger' : 'trigbits',
                                                    'tot_neutral_cal_deposition' : 'ecalneu', 'tot_cal_deposition' : 'ecaltot',
                                                    'hits' : 'tnhit', 'dedx' : 'tdedx', 'z' : 'tz', 'rho' : 'trho', 't0' : 'tt0',
                                                    'charge' : 'tcharge', 'cal_deposition' : 'ten', 
                                                    'phi' : 'tphi', 'theta' : 'tth', 'mom' : 'tptot',
                                                    'phi_v' : 'tphiv', 'theta_v' : 'tthv', 'mom_v' : 'tptotv',
                                                    'proton_index' : 'vertex_proton_track'
                                                    }, 
                                            library='pd')
        self.preprocess()
        filter_mask = self.filter()
        self.selected = self.raw[filter_mask].reset_index(drop=True)
        print('Entries after selection =', len(self.selected))
    
    def preprocess(self):
        def min_delta_phi(phis: np.ndarray)->float:
            pairs = list(itertools.combinations(phis, 2))
            delta_phi = np.array([min(abs(abs(phi1 - phi2) - np.pi), abs(phi1 - phi2)) for phi1, phi2 in pairs])
            return np.min(delta_phi)
        
        def min_delta_theta(thetas: np.ndarray)->float:
            pairs = list(itertools.combinations(thetas, 2))
            delta_theta = np.array([min(abs(theta1 + theta2 - np.pi), abs(theta1 - theta2)) for theta1, theta2 in pairs])
            return np.min(delta_theta)
        
        self.raw['delta_phi'] = self.raw['phi'].apply(lambda phi: min_delta_phi(phi))
        self.raw['delta_theta'] = self.raw['theta'].apply(lambda theta: min_delta_theta(theta))
        
        self.raw['p_max'] = self.raw['mom'].apply(lambda mom: np.max(mom))
        self.raw['p_min'] = self.raw['mom'].apply(lambda mom: np.min(mom))
        
        def get_list_without_element(init_list: list, index: int)->list:
            return init_list if index < 0 else init_list[:index] + init_list[index + 1 :]
        self.raw['vertex_min_rho'] = self.raw[['rho', 'proton_index']].\
        apply(lambda row: np.min(np.abs(get_list_without_element(row['rho'], row['proton_index']))), axis=1)
        self.raw['sigma_t0'] = self.raw['t0'].apply(lambda t0: float(np.std(t0)))
        self.raw['season'] = self.season_num
        self.raw['energy_point'] = self.energy_point_num
    
    def get_selected_entries_num(self)->int:
        return len(self.selected)
    
    def filter(self):
        self.raw['vertex_z_filter'] = self.raw['vz'].apply(lambda z: bool(np.all(np.abs(z) < self.config.max_vertex_z)))
        self.raw['vertex_track_min_rho_filter'] = self.raw['vertex_min_rho'] > self.config.vertex_track_min_rho
        self.raw['vertex_track_number_filter'] = self.raw[['phi', 'proton_index']].\
            apply(lambda row: len(row['phi']) > self.config.vertex_track_number_filter if row['proton_index'] != -1 else True, axis=1)
              
        self.raw['sigma_t0_filter'] = self.raw['sigma_t0'] < self.config.max_sigma_t0
        self.raw['tot_cal_depo_filter'] = self.raw['tot_cal_deposition'] > self.config.min_tot_cal_depo
        self.raw['p_max_filter'] = (self.config.max_p_max > self.raw['p_max']) & (self.raw['p_max']  > self.config.min_p_max)
        self.raw['p_min_filter'] = self.raw['p_min']  > self.config.min_p_min
        
        self.raw['min_vertex_rho_filter'] = self.raw['vrho'].apply(lambda z: bool(np.all(np.abs(z) > self.config.min_vertex_rho)))
        self.raw['max_vertex_rho_filter'] = self.raw['vrho'].apply(lambda z: bool(np.all(np.abs(z) < self.config.max_vertex_rho)))
                
        self.raw['collinear_filter'] = (self.raw['delta_phi']  > self.config.min_delta_phi) | (self.raw['delta_theta']  > self.config.min_delta_theta)

        filter_mask = np.array(self.raw['vertex_z_filter']) & \
                    self.raw['sigma_t0_filter'] & \
                    self.raw['tot_cal_depo_filter'] & \
                    self.raw['p_max_filter'] &\
                    self.raw['p_min_filter'] & \
                    self.raw['collinear_filter'] & \
                    self.raw['vertex_track_min_rho_filter']
                    # self.raw['min_vertex_rho_filter'] & \
                    # self.raw['max_vertex_rho_filter'] & \
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