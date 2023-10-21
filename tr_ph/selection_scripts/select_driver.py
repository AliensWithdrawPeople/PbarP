import subprocess as sub
import json
from pathlib import PurePath
import os
from enum import Enum
from multiprocessing.pool import Pool


prelim_selection_coll_macro: tuple[str, str] = ('prelim_coll.cpp', 'prelim_coll')
prelim_selection_annihilation_macro: tuple[str, str] = ('prelim_stars.cpp', 'prelim_stars')

class Event_Type(Enum):
    collinear = prelim_selection_coll_macro
    annihilation = prelim_selection_annihilation_macro
    
def get_raw_file_root_url(scan: str, point: str)->str:
    return f'root://cmd//{scan}/{scan}_tr_ph_fc_e{point}_v9.root'
    
aux1, aux2 = "\"", "\\"

def execute_selection(scan_name: str, point: str, output_name: str, event_type: Event_Type):
    prelim_selection_macro, prelim_selection_macro_name = event_type.value
    command = f"root -l -q \"select.cpp(\\{aux1 + prelim_selection_macro + aux2}\", \
                \\{aux1 + prelim_selection_macro_name + aux2}\",\
                \\{aux1 + get_raw_file_root_url(scan_name, point) + aux2}\", \
                \\{aux1 + output_name + aux2}\")\""
    res = sub.run(command, capture_output=True, shell=True)
    output = res.stderr if res.stderr else res.stdout
    print(f'[{scan_name}/{point}MeV tr_ph v9 {event_type.name} exited with {res.returncode}]', flush=True)
    print(output.decode()[118:], flush=True)

def get_selection_params_EXP(scan_points_filename: os.PathLike, event_type: Event_Type):
    if not os.path.isfile(scan_points_filename):
        raise FileNotFoundError
    with open(scan_points_filename) as file:
        scans: dict = json.load(file)
         
    selection_params= []     
    for scan_name, points in scans.items():
        for point in points:
            output_name = f'prelim/{event_type.name}/{scan_name}_e{point}_{"coll" if event_type is Event_Type.collinear else "stars"}_prelim.root'
            selection_params.append((scan_name, point, output_name, event_type))  
    return selection_params 

def execute_selection_MC(filename: str, point: str, output_name: str, event_type: Event_Type):
    prelim_selection_macro, prelim_selection_macro_name = event_type.value
    prelim_selection_macro =  'C:/work/Science/BINP/PbarP/tr_ph/selection_scripts/prelim/' + prelim_selection_macro
    command = f"root -l -q \"C:/work/Science/BINP/PbarP/tr_ph/selection_scripts/select.cpp(\\{aux1 + prelim_selection_macro + aux2}\",\
                \\{aux1 + prelim_selection_macro_name + aux2}\",\
                \\{aux1 + filename + aux2}\", \
                \\{aux1 + output_name + aux2}\")\""
    res = sub.run(command, capture_output=True, shell=True)
    output = res.stderr if res.stderr else res.stdout
    print(f'[{filename}/{point}MeV tr_ph v9 {event_type.name} exited with {res.returncode}]', flush=True)
    print(output.decode()[93:], flush=True)            
      
def get_selection_params_MC(scan_points_filename: os.PathLike, event_type: Event_Type, run_name_filter = None):
    if not os.path.isfile(scan_points_filename):
        raise FileNotFoundError
    with open(scan_points_filename) as file:
        MC_info: dict = json.load(file)

    selection_params= []     
    for run_name, info in MC_info.items():
        if run_name_filter is not None and not run_name_filter(run_name):
            continue
        season_num = info['season'][-4:] if info['season'] is not None else 0
        output_name = f'C:/work/Science/BINP/PbarP/tr_ph/root_files/MC/prelim/{event_type.name}/season{season_num}_e{info["E_beam"]}_Ge{info["Ge^2"]}_Gm{info["Gm^2"]}_{"coll" if event_type is Event_Type.collinear else "stars"}_{run_name}_prelim.root'
        selection_params.append((f'C:/work/Science/BINP/PbarP/{info["location"]}', info["E_beam"], output_name, event_type))  
    return selection_params    

############# Driver code #############
if __name__ == '__main__':
    # exp_scan_points_filename = PurePath('tr_ph/seasons.json')
    # params = get_selection_params_EXP(exp_scan_points_filename, Event_Type.collinear)
    # with Pool(4) as pool:
    #     pool.starmap(execute_selection, params)  
        
    mc_scan_points_filename = PurePath('tr_ph/MC_info.json')
    params = get_selection_params_MC(mc_scan_points_filename, Event_Type.collinear, 
                                     lambda run_name: str(run_name).startswith("run0001") or str(run_name).startswith("run0002"))
    with Pool(4) as pool:
        pool.starmap(execute_selection_MC, params) 

