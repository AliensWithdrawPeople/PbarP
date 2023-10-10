import json  
from  helper_funcs import read_compton_energy_from_dir, process_line, read_lumi_from_file


compton_energy_files_dir = 'C:/work/Science/BINP/PbarP/tr_ph/EnergyPointData/tables'
lumi_file = 'C:/work/Science/BINP/PbarP/tr_ph/lum_v9.dat'
elabels_file = 'C:/work/Science/BINP/PbarP/tr_ph/EnergyPointData/elabels.txt'
output_filename = 'C:/work/Science/BINP/PbarP/tr_ph/EnergyPointData/energy_points_data.json'

energy_df = read_compton_energy_from_dir(compton_energy_files_dir)
lumi_df = read_lumi_from_file(lumi_file)
res = {}
season = ''

with open(elabels_file, 'r') as file:
    lines = [line.strip() for line in file]
    
for line in lines:
    if line.startswith('Season'):
        season = line.rsplit('_')[-1]
        continue
    processed = process_line(line, season, energy_df, lumi_df)
    if processed is None:
        continue
    elabel, energy_point_info = processed

    res[elabel] = energy_point_info   

with open(output_filename, "w") as outfile: 
    json.dump(res, outfile, indent = 4)  
print(len(res)) 
