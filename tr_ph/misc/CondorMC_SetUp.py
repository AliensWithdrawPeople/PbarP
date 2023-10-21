import numpy as np
import json


threshold_energy = 948 # MeV
energy_points_filename = 'C:/work/Science/BINP/PbarP/tr_ph/EnergyPointData/energy_points_data.json'
with open(energy_points_filename) as file:
    elabels: dict = json.load(file)

ens = [(info['mean_energy'], elabel, info['season']) for elabel, info in elabels.items() if info['mean_energy'] > threshold_energy]
energies = [[np.round(1e-3 * 2 * en[0], 6), en[1], en[2]] for en in ens ]
events = 100000
MC_info1 = {}
MC_info2 = {}
with open("siminfo.txt", "w") as f:
    for en in energies:
        f.write(f"# season = {en[2]}\nnevents={events}\nelabel={en[1]}\nenergy={en[0]}\nQueue 1\n\n")
print(len(energies))