from scipy.cluster.hierarchy import dendrogram
import numpy as np
from matplotlib import pyplot as plt

FILENAME = "out/dendrogram"

plt.figure(figsize=(20, 10))
ax1 = plt.subplot(2,2,1)
ax2 = plt.subplot(2,2,2)
ax3 = plt.subplot(2,3,4)
ax4 = plt.subplot(2,3,5)
ax5 = plt.subplot(2,3,6)

ax = [ax1, ax2, ax3, ax4, ax5]

for i in range(5):
  file = open(FILENAME + str(i))
  dend = np.array([[float(x) for x in line.strip().split()] for line in file.readlines()])
  file.close()
  dn = dendrogram(dend, ax=ax[i])

plt.show()
