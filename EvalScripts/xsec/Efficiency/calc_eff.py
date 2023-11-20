import numpy as np
import json
import pathlib
from multiprocessing.pool import Pool

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, exp_info_path, GeGm_Fit_Result_json

GeGm = json.loads(GeGm_Fit_Result_json.read_text())
MC_info = json.loads(MC_info_path.read_text())
exp_info = json.loads(exp_info_path.read_text())

def eval_eff(elabel: str)->float:
    if elabel not in GeGm.keys():
        raise KeyError(f'No GeGm for elabel = {elabel}')
    
    if GeGm[elabel]['status'] is not True:
        raise ValueError(f'GeGm fit status is {GeGm[elabel]["status"]}') 
    info = GeGm[elabel]
    
    ge, ge_error = info['Ge2']
    gm, gm_error = info['Gm2']
    
    ge_frac = ge / (ge + gm)
    gm_frac = gm / (ge + gm)
    
    mc = list(filter(lambda run: run[1]['elabel'] == elabel, MC_info.items()))
    if len(mc) == 0:
        raise KeyError(f"No MC for elabel = {elabel}")
    if len(mc) != 2:
        raise KeyError(f"There must be exactly two MC files for elabel = {elabel}")
    ge_mc_num = 0 if mc[0][1]['Ge^2'] != 0 else 1
    ge_eff = mc[ge_mc_num][1]['eff']
    gm_eff = mc[abs(ge_mc_num - 1)][1]['eff']
    return ge_eff * ge_frac + gm_eff * gm_frac

_nominal_energy_season2019 = [str(en) for en in (936, 945, 950, 955, 962.5, 975, 978, 987.5)]
_xsec_season2019 = [0.0052, 0.0035, 0.0025, 0.2614, 0.4046, 0.4806, 0.4837, 0.5096]
vis_xsec_season2019 = dict(zip(_nominal_energy_season2019, _xsec_season2019))

_nominal_energy_season2020 = [str(en) for en in (935, 945, 950, 960, 970)]
_xsec_season2020 = [0.0022, 0.0024, 0.0035, 0.3924, 0.4637]
vis_xsec_season2020 = dict(zip(_nominal_energy_season2020, _xsec_season2020))

_nominal_energy_season2021 = [str(en) for en in (970, 980, 990, 1003.5)]
_xsec_season2021 = [0.5299, 0.4524, 0.493, 0.5064]
vis_xsec_season2021 = dict(zip(_nominal_energy_season2021, _xsec_season2021))

eff = {elabel.partition('_')[0] : eval_eff(elabel) for elabel, _ in GeGm.items() 
       if elabel in exp_info.keys() 
       and exp_info[elabel]["season"] == "HIGH2021"}

xsec_season2021 = {en : xsec / eff[en] for en, xsec in vis_xsec_season2021.items() if en in eff.keys()}
print(eff)
print(vis_xsec_season2021)
print(xsec_season2021)
# print(eval_eff("970_95392"))
# print(MC_info)