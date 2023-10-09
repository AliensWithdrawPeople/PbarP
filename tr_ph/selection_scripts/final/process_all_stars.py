from select_stars import Select_stars, make_if_not_exists, Select_config_stars
import pathlib
from config import prelim_stars_root_files_folder, final_root_files_folder


raw_files = [x for x in prelim_stars_root_files_folder.iterdir() if x.is_file() and x.suffix == '.root']
# raw_files = [pathlib.PurePath(prelim_stars_root_files_folder, 'scan2021_e970_stars_prelim.root'),
#              pathlib.PurePath(prelim_stars_root_files_folder, 'scan2021_e980_stars_prelim.root'),
#              pathlib.PurePath(prelim_stars_root_files_folder, 'scan2021_e990_stars_prelim.root'),
#              pathlib.PurePath(prelim_stars_root_files_folder, 'scan2021_e1003.5_stars_prelim.root')]

# raw_files = [pathlib.PurePath(prelim_stars_root_files_folder, 'scan2022_e937.5_stars_prelim.root')]

for file in raw_files:
    select_stars = Select_stars(file)
    energy_point_folder = pathlib.PurePath(final_root_files_folder, f'energy_{select_stars.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    select_stars.save(pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars_bkg.root'), True)