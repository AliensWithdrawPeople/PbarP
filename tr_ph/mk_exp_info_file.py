import json
import re
import pathlib


info = {}
root_files_path = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/root_files/Exp/final')
energy_dirs = [x for x in root_files_path.iterdir() if x.name.startswith('energy_') and x.is_dir()]
with open('C:/work/Science/BINP/PbarP/tr_ph/EnergyPointData/energy_points_data.json') as f:
    energy_points: dict[str, dict] = json.load(f)
    
def get_energy(dirname: str)->str | None:
    pattern = r'energy_([-+]?(?:\d*\.*\d+))MeV'
    res = re.fullmatch(pattern, dirname)
    if res is None:
        return None
    return res.group(1)

def get_year_type(filename: str)->tuple[str, str] | None:
    if not filename.startswith('season20'):
        return None
    year = filename[6:][:4]
    if not year.isdigit() or '_' not in filename:
        return None
    event_type = filename.split('_', 1)[1][:-5]
    return year, event_type

energies = dict({(get_energy(energy_dir.name), energy_dir) for energy_dir in energy_dirs if get_energy(energy_dir.name) is not None})
for energy, dir in energies.items():
    root_files = [x for x in dir.iterdir() if x.is_file() and x.suffix == '.root' and get_year_type(x.name) is not None]
    points = [(x, *get_year_type(x.name)) for x in root_files if get_year_type(x.name) is not None] # type: ignore
    for path, year, type in points:
        elabels = list(filter(lambda x: x.startswith(energy), energy_points.keys())) # type: ignore
        elabel = [elabel for elabel in elabels if energy_points[elabel]['season'][-4:].strip() == year.strip()]
        if len(elabel) != 1:
            continue
        elabel = elabel[0]
        if elabel not in info.keys():
            info[elabel] = {
                'season' : energy_points[elabel]['season'],
                'mean_energy' : energy_points[elabel]['mean_energy'],
                'location' : {},
                'lumi' : energy_points[elabel]['lumi']
            } 
        info[elabel]['location'][type] = path.as_posix()
        
with open('C:/work/Science/BINP/PbarP/tr_ph/exp_info.json', 'w') as f:
    json.dump(info, f, indent=4)
    