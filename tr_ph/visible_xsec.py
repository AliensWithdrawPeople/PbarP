from enum import Enum
import json
from pathlib import Path
import uproot as up
import re
from config import final_root_files_folder, lumi, final_tree_name

class Patterns(Enum):
    bkg_stars_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_stars_bkg.root'
    stars_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_stars.root'
    coll_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_coll.root'
    energy_point_pattern = r'energy_([-+]?(?:\d*\.*\d+))MeV'


def get_energy_point_value(energy_point_name: str)->float | int:
    match_up = re.fullmatch(Patterns.energy_point_pattern.value, energy_point_name)
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

def get_root_files(dir: Path)->list[Path]:
    return [x for x in dir.iterdir() if x.is_file() and x.suffix == '.root']

# Return (energies, xsecs, xsec_errs)
def get_xsection(season_name: str, root_file_pattern: Patterns)->tuple[list[float], list[float], list[float]]:
    with open(lumi) as file:
        lumi_data: dict = json.load(file)

    # Retrieving root files [(energy_point_name, [files])]
    events_files: list[tuple[str, list[Path]]] = [(x.name, get_root_files(x)) for x in final_root_files_folder.iterdir() if x.is_dir() and 'energy' in x.name ]
    res = {}
    for energy_point_name, files in events_files:
        energy_point = get_energy_point_value(energy_point_name)
        for file in files:
            if re.fullmatch(root_file_pattern.value, file.name) is None:
                continue

            with up.open(f'{file}:{final_tree_name}') as events:  # type: ignore
                tree = events.arrays('event_id', library='pd') # type: ignore
            entries = len(tree)
            season = file.name.split('_')[0]
            luminosity, luminosity_err = lumi_data[season][str(energy_point)][1]
            mean_energy, mean_energy_stat_err = lumi_data[season][str(energy_point)][0]
            res[(season, energy_point)] = (mean_energy, *eval_xsection(entries, luminosity, luminosity_err))


    res_filtered = dict(filter(lambda item: item[0][0] == season_name, res.items()))

    xsec = [val[1] for _, val in res_filtered.items()]
    xsec_err = [val[2] for _, val in res_filtered.items()]
    energy = [val[0] for _, val in res_filtered.items()]
    return energy, xsec, xsec_err

energy, xsec, xsec_err = get_xsection('season2022', Patterns.bkg_stars_final_root_file_pattern)
print('energy =', energy, '# MeV')
print('xsection =', xsec, '# nb')
print('xsection_error =', xsec_err, '# nb')
