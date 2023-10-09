import numpy as np

ens = np.array([970])
energy_labels = ['970_98116']

ens = list(zip(ens, energy_labels))
energies = [[np.round(1e-3 * 2 * en[0], 6), en[1]] for en in ens ]
events = 200000

with open("siminfo.txt", "w") as f:
    for en in energies:
        f.write(f"nevents={events}\nelabel={en[1]}\nenergy={en[0]}\nQueue 1\n\n")
        f.write("\n\n")