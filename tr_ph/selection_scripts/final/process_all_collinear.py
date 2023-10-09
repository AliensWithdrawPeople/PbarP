from select_coll import Select_collinear, make_if_not_exists
import pathlib
from config import prelim_coll_root_files_folder, final_root_files_folder


raw_files = [x for x in prelim_coll_root_files_folder.iterdir() if x.is_file() and x.suffix == '.root']
for file in raw_files:
    select_coll = Select_collinear(file)
    energy_point_folder = pathlib.PurePath(final_root_files_folder, f'energy_{select_coll.energy_point}MeV')
    make_if_not_exists(energy_point_folder)
    select_coll.save(pathlib.PurePath(energy_point_folder, f'{select_coll.season}_coll.root'), True)
