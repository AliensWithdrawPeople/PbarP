import json
from pathlib import Path
import jinja2

class Cook:
    def __init__(self, gegm_results: Path, energy_points_info: Path) -> None: 
        with open(gegm_results) as f:
            self.__results: dict[str, dict] = json.load(f)
            
        with open(energy_points_info) as f:
            self.__info: dict[str, dict] = json.load(f)

    def prepare_results(self):
        self.__scans: dict[str, list[tuple[float, tuple[float, float], tuple[float, float]]]] = dict()
        for elabel, res in self.__results.items():
            if 'Ge2' not in res.keys():
                continue
            if res['fit prob'] < 1e-2:
                continue
            season = self.__info[elabel]['season']
            if season not in self.__scans.keys():
                self.__scans[season] = []
            self.__scans[season].append((self.__info[elabel]['mean_energy'], res['Ge2'], res['Gm2']))
    
        aux_curly_bracket= ('{', '}')
        self.__seasons = []
        for season, vals in self.__scans.items():
            energy = []
            ratio = []
            ratio_error = []
            for val in vals:
                en, ge, gm = val
                energy.append(en)
                ge_gm_ratio = round((ge[0] / gm[0])**0.5, 4) if 10 > ge[0] > 1e-2 and 10 > gm[0] > 1e-2 else 0
                ratio.append(ge_gm_ratio)
                def eval_error(ge: tuple[float, float], gm: tuple[float, float])->float:
                    if ge[0] > 0.05 and gm[0] > 0.05:    
                        return round((ge[1]**2 * (1 / gm[0])**2 + gm[1]**2 * (ge[0] / gm[0]**2)**2)**0.5, 5)
                    return 0
                ratio_error.append(round((eval_error(ge, gm) / (2 * ge_gm_ratio)), 4) if ge_gm_ratio > 0 else 0)
            self.__seasons.append({
                'name' : season,
                'energy' : f'std::vector<double> energy_{season} = {aux_curly_bracket[0]} {", ".join([str(val) for val in energy])} {aux_curly_bracket[1]}; // MeV',
                'gegm_ratio' : f'std::vector<double> gegm_{season} = {aux_curly_bracket[0]} {", ".join([str(val) for val in ratio])} {aux_curly_bracket[1]};',
                'gegm_ratio_error' : f'std::vector<double> gegm_err_{season} = {aux_curly_bracket[0]} {", ".join([str(val) for val in ratio_error])} {aux_curly_bracket[1]};',
                
            })

    def render(self, template_filename, output_filename):
        with open(template_filename) as file_:
            self.__template = jinja2.Template(file_.read())
        rendered_content = self.__template.render(seasons=self.__seasons)
        with open(output_filename, "w") as file:
            file.write(rendered_content)
            