import numpy as np
import matplotlib.pyplot as plt
import os

# Load the points from the text file
points = np.loadtxt("points.txt", delimiter=' ', max_rows=len(list(open("./points.txt")))-1)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

plt.figure()
plt.plot(x, y, label='lines')

plt.scatter(x[0], y[0], c = 'c', label = 'point P')
plt.scatter(x[41], y[41], c = 'm', label = 'point Q')
plt.xlabel("x")
plt.ylabel("y")
plt.title("The lines formed by the points  ")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()
