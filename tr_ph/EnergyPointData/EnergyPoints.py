import pandas as pd
import pathlib

def get_energy_points()->pd.DataFrame:
    root = pathlib.Path(__file__)
    path = pathlib.Path(root.parent,  'energy_points_data.json')
    return pd.read_json(path, orient='index', convert_dates=False, convert_axes=False).reset_index(names='elabel')