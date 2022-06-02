import numpy as np
import os
from scipy.cluster.hierarchy import dendrogram
from matplotlib import pyplot as plt

DATAFILE = os.getenv("DATA_FILE")

METRIC = ["Single", "Full", "Average", "Centroid", "Ward"]

ROWS = len(METRIC)
COLS = 2

fig, ax = plt.subplots(ROWS, COLS)
fig.set_size_inches(10, 10)


file = open(DATAFILE)
points = np.array([[float(x) for x in line.strip().split()[:-1]] for line in file.readlines()])
file.close()

for met in range(ROWS):
  filename = f"out/hier/dendrogram{met}"
  file = open(filename)
  dend = np.array([[float(x) for x in line.strip().split()] for line in file.readlines()])
  file.close()

  dendrogram(dend, 100, link_color_func = lambda x : 'navy', ax=ax[met, 0], truncate_mode='lastp')
  ax[met, 0].tick_params(bottom=False, left=False, labelbottom=False, labelleft=False)
  ax[met, 0].axis("tight")
  
  filename = f"out/hier/cluster{met}"
  file = open(filename)
  cluster = np.array([int(x) for x in file.readline().strip().split()])
  file.close()

  ax[met, 1].scatter(points[:, 0], points[:, 1], c=cluster)
  ax[met, 1].tick_params(bottom=False, left=False, labelbottom=False, labelleft=False)
  ax[met, 1].axis("tight")
  # ax[met, (i - 2) % COLS].set_title("Clusters:")

fig.tight_layout()

plt.show()
