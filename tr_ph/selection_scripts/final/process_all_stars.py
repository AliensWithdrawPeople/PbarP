from select_stars import Select_stars, make_if_not_exists, Select_config_stars
import pathlib
from config import PrelimRootFilesFolder_Stars, FinalRootFilesFolder


raw_files = [x for x in PrelimRootFilesFolder_Stars.exp.value.iterdir() if x.is_file() and x.suffix == '.root']
raw_files = [pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e970_stars_prelim.root'),
             pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e980_stars_prelim.root'),
             pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e990_stars_prelim.root'),
             pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2021_e1003.5_stars_prelim.root')]

raw_files = [pathlib.PurePath(PrelimRootFilesFolder_Stars.exp.value, 'scan2022_e937.5_stars_prelim.root')]

for file in raw_files:
    select_stars = Select_stars(file)
    energy_point_folder = pathlib.PurePath(FinalRootFilesFolder.exp.value, f'energy_{select_stars.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    select_stars.save(pathlib.PurePath(energy_point_folder, f'{select_stars.season}_stars_bkg.root'), True)