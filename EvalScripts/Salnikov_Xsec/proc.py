import pandas as pd
import pathlib
import numpy as np
import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import root_folder


u1_rn = pd.read_csv(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec/Wave functions', 'U1Rn.dat'), delimiter='\t')
u1_rn['En'] = u1_rn['En'] + 2 * 938.272
u1_rn['U'] = u1_rn['Re(U)'] + u1_rn['Im(U)'] * 1.0j

u1_rp = pd.read_csv(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec/Wave functions', 'U1Rp.dat'), delimiter='\t')
u1_rp['En'] = u1_rp['En'] + 2 * 938.272
u1_rp['U'] = u1_rp['Re(U)'] + u1_rp['Im(U)'] * 1.0j

u2_rn = pd.read_csv(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec/Wave functions', 'U2Rn.dat'), delimiter='\t')
u2_rn['En'] = u2_rn['En'] + 2 * 938.272
u2_rn['U'] = u2_rn['Re(U)'] + u2_rn['Im(U)'] * 1.0j

u2_rp = pd.read_csv(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec/Wave functions', 'U2Rp.dat'), delimiter='\t')
u2_rp['En'] = u2_rp['En'] + 2 * 938.272
u2_rp['U'] = u2_rp['Re(U)'] + u2_rp['Im(U)'] * 1.0j

gp = 14.1
gn = 3.6 - 1.1j

res = pd.DataFrame({'E' : 1e-3 * u1_rn['En'], 'res' : np.absolute(gp * u1_rp['U'] + gn * u1_rn['U'])**2 + np.absolute(gp * u2_rp['U'] + gn * u2_rn['U'])**2})
with open(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec', 'Res_raw.dat'), mode='w') as f:
    f.write('std::vector<double> energies = {' + ', '.join([str(round(e, 4)) for e in list(res['E'])]) + "};\n")
    f.write('std::vector<std::complex<double>> u1_rn = {' + ', '.join([f"{round(u.real, 4)} {'+' if u.imag > 0 else '-'} {round(abs(u.imag), 4)}j"  for u in list(u1_rn['U'])]) + "};\n")
    f.write('std::vector<std::complex<double>> u1_rp = {' + ', '.join([f"{round(u.real, 4)} {'+' if u.imag > 0 else '-'} {round(abs(u.imag), 4)}j"  for u in list(u1_rp['U'])]) + "};\n")
    f.write('std::vector<std::complex<double>> u2_rn = {' + ', '.join([f"{round(u.real, 4)} {'+' if u.imag > 0 else '-'} {round(abs(u.imag), 4)}j"  for u in list(u2_rn['U'])]) + "};\n")
    f.write('std::vector<std::complex<double>> u2_rp = {' + ', '.join([f"{round(u.real, 4)} {'+' if u.imag > 0 else '-'} {round(abs(u.imag), 4)}j"  for u in list(u2_rp['U'])]) + "};\n")

res.to_csv(pathlib.PurePath(root_folder, 'EvalScripts/Salnikov_Xsec', 'Res.dat'), index=False)