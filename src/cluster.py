import numpy as np
import os
from matplotlib import pyplot as plt



met = 4
FILENAME = f"out/cluster{met}."
DATAFILE = os.getenv("DATA_FILE")

METRIC = ["Single", "Full", "Average", "Centroid", "Ward"]

ROWS = 2
COLS = 3

fig, ax = plt.subplots(ROWS, COLS)

for i in range(2, 8):
  file = open(DATAFILE)
  points = np.array([[float(x) for x in line.strip().split()[:-1]] for line in file.readlines()])
  file.close()

  file = open(FILENAME + str(i))
  cluster = np.array([int(x) for x in file.readline().strip().split()])
  file.close()

  ax[(i - 2) // COLS, (i - 2) % COLS].scatter(points[:, 0], points[:, 1], c=cluster)
  ax[(i - 2) // COLS, (i - 2) % COLS].tick_params(bottom=False, left=False, labelbottom=False, labelleft=False)
  ax[(i - 2) // COLS, (i - 2) % COLS].axis("tight")
  ax[(i - 2) // COLS, (i - 2) % COLS].set_title("Clusters:" + str(i))

fig.suptitle(METRIC[met], fontsize=16)
fig.tight_layout()

plt.show()
