from pathlib import Path
import pandas as pd
import numpy as np

def get_events_collinear(tree: pd.DataFrame, filename: Path)->tuple[float, float]:
    events = len(tree)
    events_error = events**0.5
    return events, events_error

def get_events_annihilation(tree: pd.DataFrame, filename: Path)->tuple[float, float]:
    ################# Naive event counting (const sideband) ####################################
    left_sideband: tuple[float, float] = (0.2, 0.8) # cm
    right_sideband: tuple[float, float] = (2.8, 7) # cm
    signal_zone: tuple[float, float] = (0.8, 2.8) # cm
    pipe_radius = 1.75 # cm
    vertex_rho = tree['vrho'].apply(lambda rho: rho[0])
    
    left_sideband_events_rate = len(vertex_rho[vertex_rho.between(left_sideband[0], left_sideband[1], inclusive='neither')]) / (left_sideband[1] - left_sideband[0])
    right_sideband_events_rate = len(vertex_rho[vertex_rho.between(right_sideband[0], right_sideband[1], inclusive='neither')]) / (right_sideband[1] - right_sideband[0])
    
    bkg_events_before_pipe = left_sideband_events_rate * abs(pipe_radius - signal_zone[0])
    bkg_events_after_pipe = right_sideband_events_rate * abs(signal_zone[1] - pipe_radius)
    bkg_events = bkg_events_before_pipe + bkg_events_after_pipe
    
    signal_events = len(vertex_rho[vertex_rho.between(signal_zone[0], signal_zone[1], inclusive='neither')])
    events = signal_events - bkg_events
    events_error = abs(events)**0.5 + abs(bkg_events)**0.5
    
    return events, events_error

def get_events_bkg_annihilation(tree: pd.DataFrame, filename: Path)->tuple[float, float]:
    left_sideband: tuple[float, float] = (0, 1.4)
    right_sideband: tuple[float, float] = (2.2, 7)
    signal_zone: tuple[float, float] = (1.4, 2.2)
    no_protons_filtered_tree = tree[tree['proton_index'] == -1]
    vertex_rho = no_protons_filtered_tree['vrho'].apply(lambda rho: rho[0])
    
    left_sideband_events_rate = len(vertex_rho[vertex_rho.between(left_sideband[0], left_sideband[1], inclusive='neither')]) / (left_sideband[1] - left_sideband[0])
    right_sideband_events_rate = len(vertex_rho[vertex_rho.between(right_sideband[0], right_sideband[1], inclusive='neither')]) / (right_sideband[1] - right_sideband[0])
    
    bkg_events_rate = (right_sideband_events_rate + left_sideband_events_rate) / 2
    bkg_events = bkg_events_rate * (signal_zone[1] - signal_zone[0])
    
    signal_events = len(vertex_rho[vertex_rho.between(signal_zone[0], signal_zone[1], inclusive='neither')])
    events = signal_events - bkg_events
    events_error = abs(events)**0.5 + abs(bkg_events)**0.5
    return events, events_error
