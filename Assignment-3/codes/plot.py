import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("distance.txt", delimiter=' ',max_rows=2)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

A = np.array([0, 0])
B = np.array([-1, 5])



plt.figure()  # Create a new figure for the plot
plt.plot(A[0], A[1], 'ro', label='Point A')  # Red dot for point A
plt.plot(B[0], B[1], 'bo', label='Point B')  # Blue dot for point B



plt.plot(x, y, label='Line')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Line passing given points")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()
