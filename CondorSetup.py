import json
import pathlib
import numpy as np
import pandas as pd
from tr_ph.EnergyPointData.EnergyPoints import get_energy_points
from tr_ph.config import MC_info_path

points = get_energy_points()
points = points[(points['nominal_energy'] > 930) & (points['nominal_energy'] < 950)]

ens = list(points[['mean_energy', 'elabel']].itertuples(index=False, name=None))
energies = [[np.round(1e-3 * 2 * en[0], 6), en[1]] for en in ens ]
events = 100000

with open("siminfo.txt", "w") as f:
    for en in energies:
        f.write(f"nevents={events}\nelabel={en[1]}\nenergy={en[0]}\nQueue 1\n\n")
        f.write("\n")

def MC_info_form(num: int, en: float, elabel: str):
    season = points[points['elabel'] == elabel]['season'].to_list()
    return {f"run000{num}": {
            "gen": "pp_gen",
            "location": f"tr_ph/MC/Gm/tr_ph_run000{num}.root",
            "events": 100000,
            "E_beam": en,
            "elabel": elabel,
            "Ge^2": 0,
            "Gm^2": 1,
            "B_field": 1.3,
            "Beam_smearing": True,
            "filename": "",
            "status": "ready",
            "comment": "",
            "season": season[0],
        }
    }

# files = [f.name for f in pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/MC/SortIt').iterdir() if f.is_file() and 'root' in f.suffix]
# a = dict()
# for i, en in enumerate(energies, 226):
#     if f'tr_ph_run000{i}.root' in files:
#         a.update(MC_info_form(i, en[0], en[1]))
# # print(a)
# print(MC_info_path)
# with open(MC_info_path) as f:
#     MC_info = json.load(f)
    
# with open(MC_info_path, 'w') as f:
#     MC_info.update(a)
#     json.dump(MC_info, f, indent=4)