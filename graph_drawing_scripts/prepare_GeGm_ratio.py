import json
from pathlib import Path

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import GeGm_Fit_Result_json, GeGm_Fit_Results_dir, exp_info_path

with open(Path(GeGm_Fit_Results_dir, GeGm_Fit_Result_json)) as f:
    results: dict[str, dict] = json.load(f)
    
with open(Path(exp_info_path)) as f:
    info: dict[str, dict] = json.load(f)

scans: dict[str, list[tuple[float, tuple[float, float], tuple[float, float]]]] = dict()
for elabel, res in results.items():
    if 'Ge2' not in res.keys():
        continue
    season = info[elabel]['season']
    if season not in scans.keys():
        scans[season] = []
    scans[season].append((info[elabel]['mean_energy'], res['Ge2'], res['Gm2']))
    
aux_curly_bracket= ('{', '}')
for season, vals in scans.items():
    energy = []
    ratio = []
    ratio_error = []
    for val in vals:
        en, ge, gm = val
        energy.append(en)
        ratio.append(round(ge[0] / gm[0], 5)**0.5 if ge[0] > 0.05 and gm[0] > 0.05 else 0)
        def eval_error(ge: tuple[float, float], gm: tuple[float, float])->float:
            if ge[0] > 0.05 and gm[0] > 0.05:    
                return round((ge[1]**2 * (1 / gm[0])**2 + gm[1]**2 * (ge[0] / gm[0]**2)**2)**0.5, 5)
            return 0
        ratio_error.append(eval_error(ge, gm)**0.5)
        
    print(f'// {season}')
    print(f'std::vector<double> energy_{season} ={aux_curly_bracket[0]}', ', '.join([str(val) for val in energy]), f'{aux_curly_bracket[1]}; // MeV')
    print(f'std::vector<double> gegm_{season} = {aux_curly_bracket[0]}', ', '.join([str(val) for val in ratio]), f'{aux_curly_bracket[1]};')
    print(f'std::vector<double> gegm_err_{season} = {aux_curly_bracket[0]}', ', '.join([str(val) for val in ratio_error]), f'{aux_curly_bracket[1]};\n')
