import numpy as np
import pandas as pd
from EnergyPoints import get_energy_points

points = get_energy_points()
points = points[(np.abs(points['mean_energy'] - 947.5) < 0.1) & (points['season'] == 'HIGH2022')]

print(points)