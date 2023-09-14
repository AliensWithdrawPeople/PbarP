import subprocess as sub
import json
from pathlib import PurePath
import os

prelim_selection_macro = 'prelim.cpp'
prelim_selection_macro_name = 'prelim'
    
def get_raw_file_root_url(scan: str, point: str)->str:
    return f'root://cmd//{scan}/{scan}_tr_ph_fc_e{point}_v9.root'
    
aux1, aux2 = "\"", "\\"

def execute_selection(scan_name: str, point: str, output_name: str):
    output = PurePath(f'prelim/prelim_{scan_name}', f'e{point}.root')
    if not os.path.isdir(output.parent):
        os.mkdir(output.parent)
    command = f"root -l -q \"select.cpp(\\{aux1 + prelim_selection_macro + aux2}\", \
                \\{aux1 + prelim_selection_macro_name + aux2}\",\
                \\{aux1 + get_raw_file_root_url(scan_name, point) + aux2}\", \
                \\{aux1 + output_name + aux2}\")\""
    res = sub.run(command, capture_output=True)
    output = res.stderr if res.stderr else res.stdout
    print(res.stdout.decode()[118:])

############# Main code below #############

scan_points_filename = PurePath('tr_ph_names.json')
if not os.path.isfile(scan_points_filename):
    raise FileNotFoundError
with open(scan_points_filename) as file:
    scans: dict = json.load(file)
    
for scan_name, points in scans.items():
    for point in points:
        execute_selection(scan_name, point, f'prelim_{scan_name}_e{point}_coll.root')
        