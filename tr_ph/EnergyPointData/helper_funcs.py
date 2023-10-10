import re
import pandas as pd
import pathlib

def get_energy_point_info(string: str) -> tuple[str, str, str, str, str, str] | None:
    pattern = r"([\d.]+_\d+): energy=(\d+\.\d+), runs=(\d+)-(\d+), time=\((\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}) -- (\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\)"
    match = re.match(pattern, string)

    if match:
        elabel = match.group(1)
        nominal_energy = match.group(2)
        start_run = match.group(3)
        end_run = match.group(4)
        start_date = match.group(5)
        end_date = match.group(6)
        return elabel, nominal_energy, start_run, end_run, start_date, end_date
    return None

# print(get_energy_point_info("512_36959: energy=512.0, runs=36959-36963, time=(2016-12-21 04:48:42 -- 2016-12-21 05:31:51)"))
def read_compton_energy_from_dir(dir: str)->pd.DataFrame:
    dfs = [pd.read_csv(file) for file in pathlib.Path(dir).iterdir() if file.suffix == '.csv']
    return pd.concat(dfs, ignore_index=True)

def get_season(string: str)->tuple[str, str] | None:
    pattern = r"# season id = (\d+) \(([\w/]+)\)"
    match = re.search(pattern, string)
    if match:
        season_id = match.group(1)
        season_name = match.group(2)
        return season_id, season_name
    return None
    
def read_lumi_from_file(lumi_file: str)->pd.DataFrame:
    df = pd.DataFrame(columns=['season_id', 'season_name', 'energy', 'lumi', 'lumi_error'])
    with open(lumi_file) as file:
        lines = [line.strip() for line in file]
    season_id, season_name = '', ''
    for line in lines:
        if line.startswith('//') or not line:
            continue
        if line.startswith('#'):
            season_res = get_season(line)
            if season_res is None:
                continue
            season_id, season_name = season_res
            continue
        
        energy, lumi, lumi_error, *_ = line.split()
        df.loc[len(df)] = {  # type: ignore
                            'season_id' : season_id, 
                            'season_name' : season_name, 
                            'energy' : energy, 
                            'lumi' : lumi, 
                            'lumi_error' : lumi_error
                        }
    
    return df
    
def process_line(line: str, season: str, energy_df: pd.DataFrame, lumi_df: pd.DataFrame)->tuple[str, dict] | None:
    energy_info = get_energy_point_info(line)
    if energy_info is None: 
        print(f'energy_info is None for line "{line}"; season = {season}')
        return None
    elabel, nominal_energy, start_run, end_run, start_date, end_date = energy_info
    energy = energy_df[(int(end_run) >= energy_df['first_run']) & (energy_df['first_run'] >= int(start_run))]

    if len(energy) != 1:
        print(f'Bad elabel in energy_df = {elabel}; season = {season}')
        return None
    
    lumi = lumi_df[(lumi_df['energy'] == elabel.rsplit('_')[0]) & 
                   (lumi_df['season_name'] == season)]
    if len(lumi) != 1:
        print(f'Bad elabel in lumi_df = {elabel}; season = {season}')
        return None

    res = (elabel, {
            'season' : season,
            'season_id' : lumi['season_id'].values[0],
            'nominal_energy': nominal_energy,
            'start_run': start_run,
            'end_run': end_run,
            'start_date': start_date,
            'end_date': end_date,
            'mean_energy' : energy['mean_energy'].values[0],
            'mean_energy_stat_err' : energy['mean_energy_stat_err'].values[0],
            'mean_energy_sys_err' : energy['mean_energy_sys_err'].values[0],
            'mean_spread' : energy['mean_spread'].values[0],
            'mean_spread_stat_err' : energy['mean_spread_stat_err'].values[0],
            'lumi' : lumi['lumi'].values[0],
            'lumi_error' : lumi['lumi_error'].values[0]
           }
        )
    return res