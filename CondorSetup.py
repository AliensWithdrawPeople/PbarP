import json
import pathlib
import numpy as np
import pandas as pd
from tr_ph.EnergyPointData.EnergyPoints import get_energy_points
from tr_ph.config import MC_info_path

points = get_energy_points()
points = points[points['nominal_energy'] > 938]
# print(points.sort_values(by='nominal_energy'))

ens = list(points[['mean_energy', 'elabel']].itertuples(index=False, name=None))
energies = [[np.round(1e-3 * 2 * en[0], 6), en[1]] for en in ens ]
events = 100000

MC = pathlib.Path("C:/work/Science/BINP/PbarP/tr_ph/MC/FTTP_BERT_HP")
files = [a.name for a in MC.iterdir() if 'suspicious' not in a.name]


# with open("siminfo.txt", "w") as f:
#     for en in energies:
#         f.write(f'nevents={events}\nelabel={en[1]}\nenergy={en[0]}\nshortname="{en[1]}_FTFP_BERT_HP_Ge0_Gm1"\nQueue 1\n\n')
#         # QGSP_BERT
#         # 
#         f.write("\n")
        

def MC_info_form(file: str, en: float, elabel: str, Ge, Gm):
    season = points[points['elabel'] == elabel]['season'].to_list()
    return {f"{file[:-5]}": {
            "gen": "pp_gen",
            "location": f"tr_ph/MC/FTTP_BERT_HP/{file}",
            "events": 100000,
            "E_beam": en,
            "elabel": elabel,
            "Ge^2": Ge,
            "Gm^2": Gm,
            "B_field": 1.3,
            "Beam_smearing": True,
            "filename": "",
            "status": "ready",
            "comment": "",
            "season": season[0],
            "Physics list": "FTFP_BERT_HP"
        }
    }

# files = [f.name for f in pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/MC/SortIt').iterdir() if f.is_file() and 'root' in f.suffix]
a = dict()
for file in files:
    label = file[6:].split('_FTFP_BERT_HP_')[0]
    en = round(float(file.rsplit('_')[::-1][1][2:]) * 500, 3)
    Gm = int(file.rsplit('_')[::-1][2][2:])
    Ge = int(file.rsplit('_')[::-1][3][2:])
    a.update(MC_info_form(file, en, label, Ge, Gm))
print(a)
with open(MC_info_path) as f:
    MC_info = json.load(f)

with open(MC_info_path, 'w') as f:
    MC_info.update(a)
    json.dump(MC_info, f, indent=4)