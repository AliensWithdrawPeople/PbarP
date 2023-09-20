import subprocess as sub
import json
from pathlib import PurePath
import os
from enum import Enum

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
    print(get_raw_file_root_url(scan_name, point))
    res = sub.run(command, capture_output=True, shell=True)
    output = res.stderr if res.stderr else res.stdout
    print(res.stdout.decode()[118:])

def run_EXP(scan_points_filename: os.PathLike, event_type: Event_Type):
    if not os.path.isfile(scan_points_filename):
        raise FileNotFoundError
    with open(scan_points_filename) as file:
        scans: dict = json.load(file)

    for scan_name, points in scans.items():
        for point in points:
            output_name = f'prelim/{event_type.name}/{scan_name}_e{point}_{"coll" if event_type is Event_Type.collinear else "stars"}_prelim.root'
            # print(output_name)
            execute_selection(scan_name, point, output_name, event_type)
            
      
def run_MC(MC_info_file: os.PathLike):
    # TODO
    pass        

############# Driver code #############
scan_points_filename = PurePath('tr_ph/seasons.json')
# run_EXP(scan_points_filename, Event_Type.collinear)
run_EXP(scan_points_filename, Event_Type.annihilation)
