import json
import pathlib
import subprocess as sub
from multiprocessing.pool import Pool
import re
import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, exp_info_path, GeGm_Fit_Results_dir, GeGm_Fit_Result_json

with open(MC_info_path) as f:
    MC_info: dict[str, dict] = json.load(f)
    
with open(exp_info_path) as f:
    exp_info: dict[str, dict] = json.load(f)
    
def eval_ratio(elabel: str, dist_path: str, exp_path: str, MC: list[str]):
    aux1, aux2 = "\"", "\\"
    command = f"root -l -q \"C:/work/Science/BINP/PbarP/EvalScripts/eval_GeGm_ratio.cpp(" \
                + f'\\{aux1 + dist_path + aux2}\",' \
                + f'\\{aux1 + exp_path + aux2}\",' \
                + f'\\{aux1 + MC[0] + aux2}\",' \
                + f'\\{aux1 + MC[1] + aux2}\")\"'
    res = sub.run(command, capture_output=True, shell=True)
    output = res.stderr if res.stderr else res.stdout
    output = output.decode().splitlines()
    if res.stderr:
        return elabel, {'Error' : output}
    output_data = {
        'status' : output[-1].strip()[-1:] == '0',
        'ERROR MATRIX UNCERTAINTY' : output[-11].strip()[-12:],
        'fit prob' : output[-5].strip()[10:],
        'fit chi2 / ndf' : output[-4].strip()[16:],
        'Ge2' : output[-3].strip()[6:],
        'Gm2' : output[-2].strip()[6:]
    }
    return elabel, output_data

def match_G(val: str)->tuple[float | None, float | None]:
    pattern = r'([-+]?(?:\d*\.*\d+)) \+/- ([-+]?(?:\d*\.*\d+))'
    pattern = r"([-+]?(?:\d*\.*\d+)?e[-+]?\d+|[-+]?(?:\d*\.*\d+)) \+/- ([-+]?(?:\d*\.*\d+))"
    res = re.fullmatch(pattern, val)
    if res is None or res.group(1) is None or res.group(2) is None:
        return None, None
    return (float(res.group(1)), float(res.group(2)))

params = []
for elabel, point_info in exp_info.items():
    if float(elabel.split('_')[0]) < 948 or 'coll' not in point_info['location'].keys():
        continue
    MC = [MC_point_info['processed_file_location'] for _, MC_point_info in MC_info.items() if MC_point_info['elabel'] == elabel] 
    if point_info['location'] is None or any([x is None for x in MC]):
        continue
    params.append((elabel, pathlib.Path(GeGm_Fit_Results_dir, f'season_{point_info["season"]}_elabel{elabel}_GeGm_Ratio_Res.root').as_posix(), point_info['location']['coll'], MC))

if __name__ == '__main__':
    with Pool(4) as pool:
        res = pool.starmap(eval_ratio, params)
    res = dict(res)
    keys = list(res.keys())
    keys.sort()
    sorted_dict: dict[str, dict] = {i: res[i] for i in keys}

    for elabel, res in sorted_dict.items():
        if 'Ge2' not in res.keys():
            continue
        ge, ge_error = match_G(res['Ge2'])    
        gm, gm_error = match_G(res['Gm2'])   
        res['Ge2_raw'] = res['Ge2']
        res['Gm2_raw'] = res['Gm2']
        res['Ge2'] = ge, ge_error
        res['Gm2'] = gm, gm_error
        
    with open(pathlib.Path(GeGm_Fit_Results_dir, GeGm_Fit_Result_json), 'w') as f:
        json.dump(sorted_dict, f, indent=4)
        