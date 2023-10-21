import pathlib
from enum import Enum

root_files_folder = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/root_files')

class RootFilesFolder(Enum):
    exp = pathlib.Path(root_files_folder, 'Exp')
    MC = pathlib.Path(root_files_folder, 'MC')

class PrelimRootFilesFolder(Enum):
    exp = pathlib.Path(RootFilesFolder.exp.value, 'prelim')
    MC = pathlib.Path(RootFilesFolder.MC.value, 'prelim')

class FinalRootFilesFolder(Enum):
    exp = pathlib.Path(RootFilesFolder.exp.value, 'final')
    MC = pathlib.Path(RootFilesFolder.MC.value, 'final')
    
class PrelimRootFilesFolder_Coll(Enum):
    exp = pathlib.Path(PrelimRootFilesFolder.exp.value, 'collinear')
    MC = pathlib.Path(PrelimRootFilesFolder.MC.value, 'collinear')
    
class PrelimRootFilesFolder_Stars(Enum):
    exp = pathlib.Path(PrelimRootFilesFolder.exp.value, 'stars')
    MC = pathlib.Path(PrelimRootFilesFolder.MC.value, 'stars')

lumi = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/lumi.json')
seasons = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/seasons.json')

final_tree_name = 'pbarp'


MC_info_path = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/MC_info.json')
exp_info_path = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/exp_info.json')
GeGm_Fit_Results_dir = pathlib.Path('C:/work/Science/BINP/PbarP/tr_ph/GeGmResults')

# TODO: add list of branches in final tree.