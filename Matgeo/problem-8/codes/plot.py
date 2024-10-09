import numpy as np
import matplotlib.pyplot as plt
import os

# Load the points from the text file
points = np.loadtxt("circ_parb.txt", delimiter=' ', max_rows=len(list(open("./circ_parb.txt")))-1)

#Extract x and y coordinates of circle
x_1 = points[:200, 0]
y_1 = points[:200, 1]

#Extract x and y coordinate of parabola

x_2 = points[201:500, 0]
y_2 = points[201:500, 1]

plt.figure()
plt.plot(x_1, y_1, label='Circle')
plt.plot(x_2, y_2, label='Parabola')

# Define points A, B, C
x1 = np.array([4, 4])
x2 = np.array([4, -4])
x3 = np.array([0, 0])

# Plot the specific points
plt.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1(4,4)$')
plt.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2(4,-4)$')
plt.scatter(x3[0], x3[1], color='blue', marker='o', label='Point $X_3(0,0)$')

plt.fill_between(x_2, y_2, where=(x_2 <= 4), color='darkgrey', alpha=0.3, label='$A_1$')
plt.fill_between(x_1, y_1, where=(x_1 >= 4), color='grey', alpha=0.3, label='$A_2$')
# Add text annotation
plt.text(2,0 , '$A_1$', fontsize=9, color='black')
plt.text(6,0 , '$A_2$', fontsize=9, color='black')




plt.axis('equal')
plt.xlabel("x")
plt.ylabel("y")
plt.title("The Area enclosed by parabola and circle ")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()

