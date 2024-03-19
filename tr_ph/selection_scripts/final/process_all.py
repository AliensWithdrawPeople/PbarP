import sys
sys.path.append('C:/work/Science/BINP/PbarP/tr_ph/')
import config
from Select_master import Select_master, WorkingMode, EventType

PrelimRootFilesFolders = [folder_name for folder_name in vars(config).keys() if 'PrelimRootFilesFolder_' in folder_name]
# # Set working mode
mode = WorkingMode.EXP
event_type = EventType.coll_tr_eff
_mode = 'exp' if mode is WorkingMode.EXP else 'MC'
for folder in PrelimRootFilesFolders:
    if event_type.name.strip() == folder.split('_', 1)[-1].lower().strip():
        prelim_folder = folder
        
PrelimRootFilesFolder = getattr(config, prelim_folder).__getitem__(_mode).value

phys_list = 'FTFP_BERT'
select_master = Select_master(PrelimRootFilesFolder, event_type, mode, phys_list)
select_master.execute()
