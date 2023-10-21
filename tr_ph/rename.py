import json

with open("tr_ph/MC_info.json") as file:
    MC_info: dict = json.load(file)
    
with open("tr_ph/EnergyPointData/energy_points_data.json") as file:
    energy_points: dict = json.load(file)
    
for run_name, info in MC_info.items():
    info['season'] = energy_points[info['elabel']]['season'] if info['elabel'] is not None else None
    MC_info[run_name] = info

with open("tr_ph/MC_info.json", "w") as file:
    json.dump(MC_info, file, indent = 4)  
