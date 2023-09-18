from math import pi
import os
from pathlib import PurePath
import uproot as up
import pandas as pd
import numpy as np

# Files configuration
filename = 'scan2021_e970_coll'
prelim_files_folder = PurePath("C:/work/Science/BINP/PbarP/tr_ph/root_files/prelim", "scan2021")
selected_files_folder = PurePath("C:/work/Science/BINP/PbarP/tr_ph/root_files/final", "scan2021")

# Selection configuration
max_delta_phi = 0.15
max_delta_theta = 0.2
max_z = 8
max_track_rho = 0.2
max_mom_ratio = 0.1

def make_if_not_exists(path: os.PathLike):
    if not os.path.isdir(path):
        os.mkdir(path)
        
make_if_not_exists(selected_files_folder)
raw_file = PurePath(prelim_files_folder, f"{filename}_prelim.root")
selected_file = PurePath(selected_files_folder, f"{filename}.root")
raw = up.open(f'{raw_file}:prelim') # type: ignore

raw: pd.DataFrame = raw.arrays(['event_id', 'energy', 'run', 'nt', # type: ignore
                                'tot_neutral_cal_deposition', 'tot_cal_deposition',
                                   'hits', 'dedx', 'z', 'charge', 'cal_deposition', 'rho',
                                   'phi', 'theta', 'mom',
                                   'phi_v', 'theta_v', 'mom_v'],
                      aliases={'event_id' : 'evnum', 'energy' : 'emeas', 'run' : 'runnum',
                               'tot_neutral_cal_deposition' : 'ecalneu', 'tot_cal_deposition' : 'ecaltot',
                                'hits' : 'tnhit', 'dedx' : 'tdedx', 'z' : 'tz', 'rho' : 'trho',
                               'charge' : 'tcharge', 'cal_deposition' : 'ten', 
                               'phi' : 'tphi', 'theta' : 'tth', 'mom' : 'tptot',
                               'phi_v' : 'tphiv', 'theta_v' : 'tthv', 'mom_v' : 'tptotv',
                               }, 
                      library='pd')
raw['delta_theta'] = raw['theta_v'].apply(lambda x: x[0] + x[1] - pi)
raw['delta_phi'] = raw['phi_v'].apply(lambda x: abs(x[0] - x[1]) - pi)
raw['mom_ratio'] = raw['mom_v'].apply(lambda x: abs(x[0] - x[1]) / (x[0] + x[1]))


delta_phi_filter = np.abs(raw['delta_phi']) < max_delta_phi
delta_theta_filter = np.abs(raw['delta_theta']) < max_delta_theta
z_filter = raw['z'].apply(lambda rho: bool(np.all(np.abs(rho) < max_z)))
track_rho_filter = raw['rho'].apply(lambda rho: bool(np.all(np.abs(rho) < max_track_rho)))
mom_ratio_filter = raw['mom_ratio'] < max_mom_ratio
filter_mask = delta_phi_filter & delta_theta_filter & z_filter & track_rho_filter & mom_ratio_filter
selected = raw[filter_mask].reset_index(drop=True)
print('Entries =', len(selected))

with up.recreate(selected_file) as new_file:
    new_file['pbarp'] = selected
    