import numpy as np
import matplotlib.pyplot as plt
import os

# Load the points from the text file
points = np.loadtxt("quad.txt", delimiter=',',max_rows=len(list(open("./quad.txt")))-1)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Plot the Quadrilateral
plt.figure()
plt.plot(x, y, label='Quadrilateral  Edges')
plt.fill(x, y, 'lightblue', alpha=0.5)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Quadrilateral formed by (-4,5), (0,7), (5,-5), (-4,-2)")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()
