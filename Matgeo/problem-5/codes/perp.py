import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("line_points.txt", delimiter=',')

# Extract the x and y coordinates for the points on the line1
x1 = points[:2, 0]
y1 = points[:2, 1]


# Extract the x and y coordinates for the points on the line2
x2 = points[2:4, 0]
y2 = points[2:4, 1]

# Create a figure
plt.figure()


# Plot the line1 points (blue line)
plt.plot(x1, y1, label='Line 1',color='blue', linestyle='-')
plt.xlim(-1, 1)
plt.ylim(0, 2)

# Plot the line2 points (blue line)
plt.plot(x2, y2, label='Line 2', color='red', linestyle='-')
plt.xlim(-1, 1)
plt.ylim(0, 2)


# Add labels, title, and grid
plt.xlabel("x")
plt.ylabel("y")
plt.title("Plot of lines")
plt.grid(True)
plt.legend()

plt.savefig('../figs/fig.png')
plt.show()
