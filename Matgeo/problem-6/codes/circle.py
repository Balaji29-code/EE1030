import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt

# Load the data from the file
data = np.loadtxt('circle.txt')

A = np.array((data[0]))
B = np.array((data[1]))
C = np.array((data[2]))

radius = LA.norm(C-A)

# Split data into x and y
x = data[3:, 0]
y = data[3:, 1]

# Plot the data
plt.plot(x, y, label = 'Circle')

txtA = 'A(2,4)'
txtB = 'B' 

plt.scatter(data[0, 0], data[0, 1], c = 'c', label = txtA)
plt.scatter(data[1, 0], data[1, 1], c = 'm', label = txtB)
plt.annotate(txtA, xy = A)
plt.annotate(txtB, xy = B)

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Plot of Circle')
plt.axis('equal')
plt.grid(True)
plt.legend(loc = 'upper right')

plt.savefig('../figs/fig.png')
plt.show()
