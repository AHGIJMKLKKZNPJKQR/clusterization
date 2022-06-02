import numpy as np
import os
import matplotlib.ticker as ticker
from matplotlib import pyplot as plt

DATAFILE = os.getenv("DATA_FILE")


filename = f"out/kmeans/elbow"
file = open(filename)
err = np.array([float(x) for x in file.readline().strip().split()])
file.close()

fig, ax = plt.subplots()

ax.plot(range(1, 11), err)
ax.tick_params(left=False, labelleft=False)
ax.xaxis.set_major_locator(ticker.MultipleLocator(1))  
plt.grid(True, axis = 'x')
plt.show()
