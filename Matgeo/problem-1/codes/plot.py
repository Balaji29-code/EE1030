import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt

# Load the data from the file
data = np.loadtxt('point.txt')

P = np.array((data[0]))
Q = np.array((data[1]))
R = np.array((data[2]))

txtP = 'P(2,-2)'
txtQ = 'Q(3,7)'
txtR = 'R(2.18,-0.36)'


x = data[3:, 0]
y = data[3:, 1]


plt.plot(data[0:3, 0], data[0:3, 1], label = 'Line')
plt.scatter(data[0, 0], data[0, 1], c = 'c', label = txtP)
plt.scatter(data[1, 0], data[1, 1], c = 'm', label = txtQ)
plt.scatter(data[2, 0], data[2, 1], c = 'y', label = txtR)

plt.annotate(txtP, xy = P)
plt.annotate(txtQ, xy = Q)
plt.annotate(txtR, xy = R)

plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Plot of the line')
plt.axis('equal')
plt.grid(True)
plt.legend(loc = 'upper left')

plt.savefig('../figs/fig.png', format='png')
plt.show()
