from enum import Enum, member
from pathlib import Path
import re
from typing import Callable
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