from enum import Enum, member
from pathlib import Path
import re
import json

import jinja2
import pandas as pd 

from EventCounter import get_events_collinear, get_events_annihilation, get_events_bkg_annihilation

class Patterns(Enum):
    bkg_stars_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_stars_bkg.root'
    stars_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_stars.root'
    coll_final_root_file_pattern = r'season([-+]?(?:\d*\.*\d+))_coll.root'
    energy_point_pattern = r'energy_([-+]?(?:\d*\.*\d+))MeV'


def get_energy_point_value(energy_point_name: str)->float | int:
    matched_values = re.fullmatch(Patterns.energy_point_pattern.value, energy_point_name)
    energy_point_val = matched_values.group(1) #type: ignore
    return float(energy_point_val) if len(energy_point_val.rsplit('.')) != 1 else int(energy_point_val)

def eval_xsection(entries: float, entries_err: float, luminosity: float, luminosity_err: float)->tuple[float, float]:
    """Evaluate cross section

    Parameters
    ----------
    entries : float
    entries_err : float
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
    xsection_error = (1 / (luminosity**2) * entries_err**2 +  (entries / (luminosity**2))**2 * luminosity_err**2)**0.5
    return round(xsection, 4), round(xsection_error, 4)

def get_root_files(dir: Path)->list[Path]:
    return [x for x in dir.iterdir() if x.is_file() and x.suffix == '.root']


class EventType(Enum):
    collinear = member(get_events_collinear)
    annihilation = member(get_events_annihilation)
    bkg_annihilation = member(get_events_bkg_annihilation)
    
def get_entries(event_type: EventType, vertex_rho: pd.DataFrame)-> tuple[float, float]:
    return event_type.value(vertex_rho) # type: ignore

def render(data, template_filename, output_filename):
    with open(template_filename) as file_:
        template = jinja2.Template(file_.read())
    rendered_content = template.render(seasons=data)
    with open(output_filename, "w") as file:
        file.write(rendered_content)
        

def format_data(data: dict[str, list[float] | str], exp_info_path: Path):
    exp_info = json.loads(exp_info_path.read_text())
    formatted = {}
    for nominal_energy, energy, xsec, xsec_error in zip(data['nominal_energy'], data['energy'], data['xsec'], data['xsec_error']):
        info = [(elabel, info) for elabel, info in exp_info.items() if 
                  info['season'][-4:] == data['season'][-4:] and 
                  elabel.partition('_')[0] == str(nominal_energy) and
                  abs(info['mean_energy'] - energy) < 0.1]
        if len(info) != 1:
            print(f"bruh! Can't find your bloody elabel! Take a look at these elabels = {[v[0] for v in info]} (season = {data['season']}, energy = {nominal_energy}).")
            continue
        elabel, info = info[0]
        formatted[elabel] = {
            "season" : info['season'],
            "nominal_energy" :nominal_energy,
            "energy" : energy,
            "cross section" : xsec,
            "cross section error" : xsec_error
        }
    return formatted
