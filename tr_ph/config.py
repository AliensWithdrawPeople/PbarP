import pathlib
from enum import Enum

root_folder = pathlib.Path('C:/work/Science/BINP/PbarP/')

root_files_folder = pathlib.Path(root_folder, 'tr_ph/root_files')

class RootFilesFolder(Enum):
    exp = pathlib.Path(root_files_folder, 'Exp')
    MC = pathlib.Path(root_files_folder, 'MC')

class PrelimRootFilesFolder(Enum):
    exp = pathlib.Path(RootFilesFolder.exp.value, 'prelim')
    MC = pathlib.Path(RootFilesFolder.MC.value, 'prelim')

class FinalRootFilesFolder(Enum):
    exp = pathlib.Path(RootFilesFolder.exp.value, 'final')
    MC = pathlib.Path(RootFilesFolder.MC.value, 'final')
    
class PrelimRootFilesFolder_Coll(Enum):
    exp = pathlib.Path(PrelimRootFilesFolder.exp.value, 'collinear')
    MC = pathlib.Path(PrelimRootFilesFolder.MC.value, 'collinear')
    
class PrelimRootFilesFolder_Stars(Enum):
    exp = pathlib.Path(PrelimRootFilesFolder.exp.value, 'stars')
    MC = pathlib.Path(PrelimRootFilesFolder.MC.value, 'stars')

class PrelimRootFilesFolder_Coll_Track_Eff(Enum):
    exp = pathlib.Path(PrelimRootFilesFolder.exp.value, 'collinear_track_efficiency')
    MC = pathlib.Path(PrelimRootFilesFolder.MC.value, 'collinear_track_efficiency')
    
lumi = pathlib.Path(root_folder, 'tr_ph/lumi.json')
seasons = pathlib.Path(root_folder, 'tr_ph/seasons.json')

MC_info_path = pathlib.Path(root_folder, 'tr_ph/MC_info.json')
exp_info_path = pathlib.Path(root_folder, 'tr_ph/exp_info.json')
GeGm_Fit_Results_dir = pathlib.Path(root_folder, 'tr_ph/GeGmResults')
GeGm_Fit_Result_json = pathlib.Path(GeGm_Fit_Results_dir, 'raw_GeGm_Ratio_Res.json')

collinear_results_data = pathlib.Path(root_folder, 'Results', 'collinear.json')
stars_results_data = pathlib.Path(root_folder, 'Results', 'stars.json')

templates = pathlib.Path(root_folder, 'graph_drawing_scripts/templates/')

final_tree_name = 'pbarp'

class final_tree_branches(Enum):
    coll = ['season', 'energy_point', 'event_id', 'energy', 'run',
            'nt', 'tot_neutral_cal_deposition', 'tot_cal_deposition',
            'hits', 'dedx', 'z', 'charge', 'cal_deposition', 'rho',
            'phi', 'theta', 'mom',
            'phi_v', 'theta_v', 'mom_v'
            'delta_theta', 'delta_phi', 'mom_ratio',
            # fake branches:
            'vrho', 'proton_index']
    stars = ['season', 'energy_point', 'event_id', 'energy', 'run', 'nt', 'min_rho', 'trigger',
            'vrho', 'vz', 'is_coll', 'proton_index', 'vtrk',
            'tot_neutral_cal_deposition', 'tot_cal_deposition',
            'hits', 'dedx', 'z', 'charge', 'cal_deposition', 'rho', 't0', 'tant',
            'phi', 'theta', 'mom',
            'phi_v', 'theta_v', 'mom_v'
            'delta_phi', 'delta_theta',
            'p_max', 'p_min',
            'vertex_min_rho', 'sigma_t0',
            'vertex_z_filter' 'vertex_track_min_rho_filter', 'vertex_track_number_filter'
            'sigma_t0_filter', 'tot_cal_depo_filter', 'collinear_filter',
            'p_max_filter', 'p_min_filter',
            'min_vertex_rho_filter', 'max_vertex_rho_filter']
    
    coll_track_efficiency = ['season', 'energy_point' , 'event_id', 'energy', 'run',
                            'tot_neutral_cal_deposition', 'tot_cal_deposition',
                            'proton_hits', 'proton_dedx', 'proton_z', 'proton_cal_deposition', 'proton_rho',
                            'proton_phi', 'proton_theta', 'proton_mom',
                            'proton_phi_v', 'proton_theta_v', 'proton_mom_v',
                            'antiproton_hits', 'antiproton_dedx', 'antiproton_z', 'antiproton_cal_deposition', 'antiproton_rho',
                            'antiproton_phi', 'antiproton_theta', 'antiproton_mom',
                            'antiproton_phi_v', 'antiproton_theta_v', 'antiproton_mom_v',
                            'found_both']
    