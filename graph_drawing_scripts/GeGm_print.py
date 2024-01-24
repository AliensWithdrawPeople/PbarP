from GeGm_Result.prepare_GeGm_ratio import Cook
import subprocess as sub
from pathlib import Path
import sys
sys.path.append('C:/work/Science/BINP/PbarP')
from tr_ph.config import GeGm_Fit_Result_json, GeGm_Fit_Result_json_eff_corrected, GeGm_Fit_Results_dir, exp_info_path

template_filename = 'C:/work/Science/BINP/PbarP/graph_drawing_scripts/GeGm_Result/GeGmRatio_result_template.cpp.jinja'
output_filename = 'C:/work/Science/BINP/PbarP/graph_drawing_scripts/GeGm_Result/GeGmRatio_result.cpp' 
results = Path(GeGm_Fit_Results_dir, GeGm_Fit_Result_json_eff_corrected)
exp_info = Path(exp_info_path)


cook = Cook(results, exp_info)
cook.prepare_results()
cook.render(template_filename, output_filename, draw_chi2 = False)
   
aux1, aux2 = "\"", "\\"
command = f'root -l \"{output_filename}\"'
res = sub.run(command, capture_output=True, shell=True)
output = res.stderr if res.stderr else res.stdout