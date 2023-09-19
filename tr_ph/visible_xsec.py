import json
from pathlib import Path
import uproot as up
import re
from config import final_root_files_folder, lumi, final_tree_name

def get_energy_point_value(energy_point_name: str)->float | int:
    energy_point_pattern = r'energy_([-+]?(?:\d*\.*\d+))MeV'
    match_up = re.fullmatch(energy_point_pattern, energy_point_name)
    energy_point_val = match_up.group(1) #type: ignore
    return float(energy_point_val) if len(energy_point_val.rsplit('.')) != 1 else int(energy_point_val)

def eval_xsection(entries: int, luminosity: float, luminosity_err: float)->tuple[float, float]:
    """Evaluate cross section

    Parameters
    ----------
    entries : int
    luminosity : float
    luminosity_err : float

    Returns
    -------
    tuple[float, float]
        (xsection, xsection_error)
    """
    if abs(luminosity) <  1e-6 or abs(luminosity_err) <  1e-6:
        return 0, 0
    xsection = entries / luminosity
    xsection_error = (entries / (luminosity**2) +  (entries / (luminosity**2))**2 * luminosity_err**2)**0.5
    return round(xsection, 4), round(xsection_error, 4)
    
with open(lumi) as file:
    lumi_data: dict = json.load(file)

def get_root_files(dir: Path)->list[Path]:
    return [x for x in dir.iterdir() if x.is_file() and x.suffix == '.root']
# [(energy_point_name, [files])]
coll_events_files: list[tuple[str, list[Path]]] = [(x.name, get_root_files(x)) for x in final_root_files_folder.iterdir() if x.is_dir() and 'energy' in x.name]

res = {}
for energy_point_name, files in coll_events_files:
    energy_point = get_energy_point_value(energy_point_name)
    for file in files:
        with up.open(f'{file}:{final_tree_name}') as coll_events:  # type: ignore
            tree = coll_events.arrays('event_id', library='pd') # type: ignore
        entries = len(tree)
        season = file.name.split('_')[0]
        luminosity, luminosity_err = lumi_data[season][str(energy_point)]
        res[(season, energy_point)] = eval_xsection(entries, luminosity, luminosity_err)


res_filtered = dict(filter(lambda item: item[0][0] == 'season2022', res.items()))

xsec = [val[0] for _, val in res_filtered.items()]
xsec_err = [val[1] for _, val in res_filtered.items()]
energy = [key[1] for key, _ in res_filtered.items()]
print('energy =', energy)
print('xsection =', xsec)
print('xsection_error =', xsec_err)
