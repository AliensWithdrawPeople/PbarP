import json
import pathlib
import subprocess as sub
from multiprocessing.pool import Pool
import re
import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, exp_info_path, GeGm_Fit_Results_dir, GeGm_Fit_Result_json, GeGm_Fit_Result_json_eff_corrected

with open(MC_info_path) as f:
    MC_info: dict[str, dict] = json.load(f)
    
with open(exp_info_path) as f:
    exp_info: dict[str, dict] = json.load(f)
    
def eval_eff(elabel: str, exp_path: str, MC: list[str], result_file_name: str, result_name: str):
    aux1, aux2 = "\"", "\\"
    script_name = "get_track_eff"
    command = f"root -l -q \"C:/work/Science/BINP/PbarP/EvalScripts/track_eff/{script_name}.cpp(" \
                + f'\\{aux1 + exp_path + aux2}\",' \
                + f'\\{aux1 + MC[0] + aux2}\",' \
                + f'\\{aux1 + MC[1] + aux2}\",' \
                + f'\\{aux1 + result_file_name + aux2}\",' \
                + f'\\{aux1 + result_name + aux2}\",' \
                + f'\\{aux1 + elabel+ aux2}\")\"'
    res = sub.run(command, capture_output=True, shell=True)
    output = res.stderr if res.stderr else res.stdout
    output = output.decode().splitlines()

params = []
names = {}
for elabel, point_info in exp_info.items():
    if float(elabel.split('_')[0]) < 950 or 'coll' not in point_info['location'].keys():
        continue
    MC = [MC_point_info['tr_eff processed_file_location'] for _, MC_point_info in MC_info.items() if MC_point_info['elabel'] == elabel and 'tr_eff processed_file_location' in MC_point_info.keys()] 
    if point_info['location'] is None or any([x is None for x in MC]):
        continue
    if f'season_{point_info["season"]}' not in names.keys():
        names[f'season_{point_info["season"]}'] = []
    result_name = elabel.split('_')[1]
    names[f'season_{point_info["season"]}'].append((f'season_{point_info["season"]}_elabel{elabel}_track_eff_res.root', result_name))
    params.append((elabel, point_info['location']['coll_tr_eff'], MC, 
                   pathlib.Path('C:/work/Science/BINP/PbarP/EvalScripts/track_eff', f'season_{point_info["season"]}_elabel{elabel}_track_eff_res.root').as_posix(), result_name))

for par in params:
    eval_eff(*par)
print(f'std::vector<std::string> seasons = ' + '{"' + '", "'.join(names.keys())  + '"};')

for season in names.keys():
    print(f'// Season: {season[7:]}')
    print(f'std::vector<std::string> names_{season} = ' + '{"' + '", "'.join([name for name, label in names[season]])  + '"};')
    print(f'std::vector<std::string> label_{season} = ' + '{"' + '", "'.join([label for name, label in names[season]])  + '"};')
    # for name in names[season]:
    #     print(name[0], name[1])