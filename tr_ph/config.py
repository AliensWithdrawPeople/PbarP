import pathlib

root_files_folder = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/root_files')
prelim_root_files_folder = pathlib.Path(root_files_folder, 'prelim')
final_root_files_folder = pathlib.Path(root_files_folder, 'final')

prelim_coll_root_files_folder = pathlib.Path(prelim_root_files_folder, 'collinear')
prelim_stars_root_files_folder = pathlib.Path(prelim_root_files_folder, 'stars')

lumi = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/lumi.json')
seasons = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/seasons.json')

final_tree_name = 'pbarp'

# TODO: add list of branches in final tree.