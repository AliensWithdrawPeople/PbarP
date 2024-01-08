import json
from scipy.optimize import curve_fit
import numpy as np

import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import MC_info_path, collinear_results_data, stars_results_data, GeGm_Fit_Result_json, templates, root_folder

ev_type = "stars"
results_data = collinear_results_data if ev_type == "coll" else stars_results_data
eff_key_name = 'eff' if ev_type == "coll" else 'eff_stars'

GeGm = json.loads(GeGm_Fit_Result_json.read_text())
MC_info = json.loads(MC_info_path.read_text())
vis_xsec_data = json.loads(results_data.read_text())

def get_effs(elabel: str)->tuple[float, float]:
    mc = list(filter(lambda run: run[1]['elabel'] == elabel, MC_info.items()))
    if len(mc) == 0:
        raise KeyError(f"No MC for elabel = {elabel}")
    if len(mc) != 2:
        raise KeyError(f"There must be exactly two MC files for elabel = {elabel}")
    ge_mc_num = 0 if mc[0][1]['Ge^2'] != 0 else 1
    gm_mc_num = 1 if mc[0][1]['Ge^2'] != 0 else 0
    
    eff_ge = mc[ge_mc_num][1][eff_key_name]
    eff_gm = mc[gm_mc_num][1][eff_key_name]
    return eff_ge, eff_gm

eff_ge_dicts = dict()
eff_gm_dicts = dict()

energy_data = []
xsection_dict = dict()
xsection_data = []
xsection_err_data = []
for elabel, xsec in vis_xsec_data.items():
    if not (940 < xsec['nominal_energy'] < 952):
        continue
    try:
        eff_ge, eff_gm = get_effs(elabel)
    except KeyError as e:
        print(e)
        continue
    energy, xsection, xsection_err = xsec['energy'], xsec["cross section"], xsec["cross section error"]
    eff_ge_dicts[energy] = eff_ge
    eff_gm_dicts[energy] = eff_gm
    xsection_dict[energy] = xsection
    energy_data.append(energy)
    xsection_data.append(xsection)
    xsection_err_data.append(xsection_err)

def func(energy, gegm_ratio, const_xsec):
    if(type(energy) is np.ndarray):
        eff_ge = []
        eff_gm = []
        for en in energy:
            eff_ge.append(eff_ge_dicts[en])
            eff_gm.append(eff_gm_dicts[en])  
        eff_ge = np.array(eff_ge)
        eff_gm = np.array(eff_gm)   
        ge_frac = gegm_ratio / (1 + gegm_ratio)
        gm_frac = 1 / (1 + gegm_ratio)
        eff = eff_ge * ge_frac + eff_gm * gm_frac
        return const_xsec * eff
    
    ge_frac = gegm_ratio / (1 + gegm_ratio)
    gm_frac = 1 / (1 + gegm_ratio)
    eff = eff_ge_dicts[energy] * ge_frac + eff_gm_dicts[energy] * gm_frac
    return const_xsec * eff
popt, pcov = curve_fit(func, energy_data, xsection_data, sigma=xsection_err_data, absolute_sigma=True, bounds=[(0., 0.1), (2, 2)], p0=(1, 0.8))
gegm_ratio = popt[0]
gegm_ratio_err = np.sqrt(np.diag(pcov))[0]
# gegm_ratio = 1
# gegm_ratio_err = 0.1

eff_ge = []
eff_gm = []
for en in energy_data:
    eff_ge.append(eff_ge_dicts[en])
    eff_gm.append(eff_gm_dicts[en])  
eff_ge = np.array(eff_ge)
eff_gm = np.array(eff_gm)   

events = 1e5
ge_frac = gegm_ratio / (1 + gegm_ratio)
gm_frac = 1 / (1 + gegm_ratio)
eff = eff_ge * ge_frac + eff_gm * gm_frac
eff_error = (ge_frac**2 * (eff_ge * (1 - eff_ge) / (events)**0.5)**2 + 
            gm_frac**2 * (eff_gm * (1 - eff_gm) / (events)**0.5)**2 +
            1/(1 + gegm_ratio)**4 * (eff_ge - eff_gm)**2)**0.5
xsection_data = np.array(xsection_data)
xsection_err_data = np.array(xsection_err_data)

xsection_err_data = ((xsection_err_data / eff)**2 + (xsection_data * eff_error / eff**2)**2)**0.5
xsection_data = xsection_data / eff

print(popt)
print(list(np.round(energy_data, 4)))
print(list(np.round(xsection_data, 4)))
print(list(np.round(xsection_err_data, 4)))
print('eff_ge =', list(np.round(eff_ge, 4)))
print('eff_ge error =', list(np.round((eff_ge * (1 - eff_ge) / (events)**0.5), 4)))
print('eff_gm =', list(np.round(eff_gm, 4)))
print('eff_gm error =', list(np.round((eff_gm * (1 - eff_gm) / (events)**0.5), 4)))
print(np.sqrt(np.diag(pcov)))
