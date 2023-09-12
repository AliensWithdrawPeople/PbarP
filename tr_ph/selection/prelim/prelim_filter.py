from math import pi
import os
import pathlib
import numpy as np
import uproot as up
import pandas as pd

class Prelim_Selector:
    max_rho_cut: float = 1. # cm.
    min_de_dx: float = 6e3
    max_de_dx: float = 3e4
    rho_gate: tuple[float, float] = (2, 1)
    vertex_min_track_number: float = 3
    max_energy_deposition_per_track: float = 400
    
    def __init__(self, path: str, tree_name: str):
        tree = up.open(f"{path}:{tree_name}")
        self.events: pd.DataFrame = tree.arrays(["id", "ebeam", "emeas", "demeas", "xbeam", "ybeam", # type: ignore
                                                "runnum", "is_coll", "is_bhabha", "ecaltot", "ecalneu"],
                                                aliases={"id" : "evnum"}, library="pd")
        
        self.vertices: pd.DataFrame = tree.arrays(["id", "num", "trk", "tracks_idx", "rho"], # type: ignore
                                                    aliases={"id" : "evnum", "num": "nv", "trk" : "vtrk", "tracks_idx" : "vind", "rho" : "vxyz"}, 
                                                    library="pd")
        self.calc_rho = lambda r: np.sqrt(r[0]**2 + r[1]**2) if len(r) == 3 else -1
        self.vertices['rho'] = self.vertices['rho'].map(lambda coords: list(map(self.calc_rho, coords)))
        
        self.tracks: pd.DataFrame = tree.arrays(["id", "nt", "nhit", "length", "phi", "theta", # type: ignore
                            "ptot", "phi_v", "theta_v", "ptot_v",
                            "rho", "dedx", "z", "t0", "ant", 
                            "charge", "energy_deposition"], 
                            aliases={"id" : "evnum", "nhit" : "tnhit", "length" : "tlength", 
                                    "phi" : "tphi", "theta" : "tth", 
                                    "ptot" : "tptot", "phi_v" : "tphiv", 
                                    "theta_v" : "tthv", "ptot_v" : "ptotv", 
                                    "rho" : "trho", "dedx" : "tdedx", 
                                    "z" : "tz", "t0" : "tt0[good_idx]", "ant" : "tant", 
                                    "charge" : "tcharge", "energy_deposition" : "ten"},
                            library="pd")
        
        self.photons: pd.DataFrame = tree.arrays(["id", "nph_total", "nph", "phen", "phth", "phphi", "phen0", "phth0", "phphi0"], # type: ignore
                                                 aliases={"id" : "evnum",}, library="pd")
        
        self.pbar_p: pd.DataFrame = pd.DataFrame(data={"id" : self.events["id"]})
        self.flags: pd.DataFrame = pd.DataFrame(data={"id" : self.events["id"],
                                                    "is_coll" : self.__process_is_coll(self.tracks, self.max_rho_cut, self.min_de_dx, self.max_de_dx), 
                                                    "is_annihilation" : self.__process_is_annihilation(self.tracks, self.vertices, self.rho_gate,
                                                                        self.vertex_min_track_number, self.max_energy_deposition_per_track)})
        
        def delta_phi(phi)->float | None:
            if len(phi) != 2:
                return None
            return abs(phi[0] - phi[1]) - pi
        
        def delta_theta(theta)->float | None:
            if len(theta) != 2:
                return None
            return theta[0] + theta[1] - pi
        
        prepared_df = self.tracks[['phi', 'theta']].join(self.flags['is_coll'])
        self.pbar_p: pd.DataFrame = pd.DataFrame(data={"id" : self.events["id"], 
                                                       "delta_phi" : prepared_df.apply(lambda x: delta_phi(x['phi'][x['is_coll']]), axis=1), # type: ignore
                                                       "delta_theta" : prepared_df.apply(lambda x: delta_theta(x['theta'][x['is_coll']]), axis=1)}) # type: ignore
        
    def __process_is_coll(self, tracks: pd.DataFrame, max_rho_cut, min_de_dx, max_de_dx)->list:
        is_coll = []
        for _, track in tracks.iterrows():
            mask = (track['rho'] < max_rho_cut) & (max_de_dx > track['dedx']) & (track['dedx'] > min_de_dx)
            charges = track['charge'][mask]
            is_coll.append(mask & (len(charges) == 2 and charges[0] * charges[1] < 0))
        return is_coll
    
    def __process_is_annihilation(self, tracks: pd.DataFrame, vertices: pd.DataFrame, rho: tuple[float, float], 
                                vertex_min_track_number: float, max_energy_deposition_per_track: float)->list:
        is_annihilation = []
        for _, vertex in vertices.iterrows():
            mask: pd.Series[bool] = vertex['rho'].apply(lambda x: rho[1] > x > rho[0]) & (vertex['trk'] >= vertex_min_track_number)
            if not mask.any():
                is_annihilation.append(mask & False)
                continue
            calorimeter_filter: pd.Series[bool] = tracks[tracks['id'] == vertex['id']]["energy_deposition"] < max_energy_deposition_per_track
            if calorimeter_filter.any():
                is_annihilation.append(mask & False)
                continue
            is_annihilation.append(mask)
        return is_annihilation
    
    def save(self, path: os.PathLike, tree_name: str):
        path = pathlib.PurePath(path)
        if os.path.isfile(path):
            raise FileExistsError(f"File with name {path.name} in folder {path.parent} already exist, pal.")
        file = up.recreate(path)
        df = self.events.join(self.vertices.set_index('id'), on='id')
        df = df.join(self.tracks.set_index('id'), on='id')
        df = df.join(self.photons.set_index('id'), on='id')
        df = df.join(self.pbar_p.set_index('id'), on='id')
        df = df.join(self.flags.set_index('id'), on='id')
        file[tree_name] = df