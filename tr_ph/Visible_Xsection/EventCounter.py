import pandas as pd
import numpy as np

def get_events_collinear(tree: pd.DataFrame)->tuple[float, float]:
    events = len(tree)
    events_error = events**0.5
    return events, events_error

def get_events_annihilation(tree: pd.DataFrame)->tuple[float, float]:
    left_sideband: tuple[float, float] = (0, 1.4)
    right_sideband: tuple[float, float] = (2.2, 7)
    signal_zone: tuple[float, float] = (1.4, 2.2)
    
    vertex_rho = tree['vrho'].apply(lambda rho: rho[0])
    
    left_sideband_events_rate = len(vertex_rho[vertex_rho.between(left_sideband[0], left_sideband[1], inclusive='neither')]) / (left_sideband[1] - left_sideband[0])
    right_sideband_events_rate = len(vertex_rho[vertex_rho.between(right_sideband[0], right_sideband[1], inclusive='neither')]) / (right_sideband[1] - right_sideband[0])
    
    bkg_events_rate = (right_sideband_events_rate + left_sideband_events_rate) / 2
    bkg_events = bkg_events_rate * (signal_zone[1] - signal_zone[0])
    
    signal_events = len(vertex_rho[vertex_rho.between(signal_zone[0], signal_zone[1], inclusive='neither')])
    events = signal_events - bkg_events
    events_error = abs(events)**0.5 + abs(bkg_events)**0.5
    return events, events_error

def get_events_bkg_annihilation(tree: pd.DataFrame)->tuple[float, float]:
    events = len(tree)
    events_error = events**0.5
    return events, events_error
