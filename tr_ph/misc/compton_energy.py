import pandas as pd


ens = [930, 936, 937.4, 937.5, 938.3, 938.9, 939.6, 940.2, 940.3, 940.8, 942, 950, 960, 971, 981]

url = "https://cmd.inp.nsk.su/~compton/gitlist/compton_tables/raw/dev/tables/HIGH2017.csv"
df = pd.read_csv(url)
vals = df[df['energy_point'].isin(ens)][["energy_point", "mean_energy", "mean_energy_stat_err"]]
for val in vals.values:
    print(val[0], f"[{val[1]}, {val[2]}],")
    