import numpy as np
import os
from scipy.cluster.hierarchy import dendrogram
from matplotlib import pyplot as plt

DATAFILE = os.getenv("DATA_FILE")

MAXK = int(os.getenv("MAX_K"))

ROWS = (MAXK+1)//2
COLS = 2

fig, ax = plt.subplots(ROWS, COLS)
fig.set_size_inches(10, 10)


# file = open(DATAFILE)
file = open("data/normalized.txt")
points = np.array([[float(x) for x in line.strip().split()] for line in file.readlines()])
file.close()

for k in range(MAXK):
  filename = f"out/kmeans/cluster{k + 1}"
  file = open(filename)
  cluster = np.array([int(x) for x in file.readline().strip().split()])
  file.close()

  ax[k % ROWS, k // ROWS].scatter(points[:, 0], points[:, 1], c=cluster)
  # ax[k % ROWS, k // ROWS].tick_params(bottom=False, left=False, labelbottom=False, labelleft=False)
  ax[k % ROWS, k // ROWS].axis("tight")

fig.tight_layout()

plt.show()
