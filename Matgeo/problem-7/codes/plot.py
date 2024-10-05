import numpy as np
import matplotlib.pyplot as plt
import math

# Load points from the file
points = np.loadtxt('parab.dat', delimiter=',', max_rows=len(list(open("./parab.dat")))-1)

# Extract x and y values
x = points[:, 0]
y = points[:, 1]

# Define points A, B, C, D
x1 = np.array([11.3, 11.3])
x2 = np.array([11.3, -11.3])

# Plot the parabola
plt.plot(x, y, label='Parabola')

# Plot the specific points
plt.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1$(11.3,11.3)')
plt.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2$(11.3,-11.3)')

# Define the line equation x = 8*\sqrt2
line_y = np.linspace(min(y), max(y), 400)
line_x = line_y * 0 + 8*math.sqrt(2)

# Plot the line x=11.3
plt.plot(line_x, line_y, color='green', label='Line: x = 11.3')

plt.text(x1[0] + 0.2, x1[1] - 0.3, '$X_1(11.3,11.3)$', color='green', fontsize=9)
plt.text(x2[0] + 0.2, x2[1] - 0.3, '$X_2(11.3,-11.3)$', color='red', fontsize=9)

# Fill the closed region between the parabola and the line x=2
# We want to fill only the region where x <= 2 (parabola on the left of the line)
plt.fill_between(x, y, where=(x <= 11.3), color='blue', alpha=0.3, label='Shaded Region')

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Parabola, Line, and Points $X_1$ & $X_2$")
plt.grid(True)
plt.legend(loc='upper left')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()
