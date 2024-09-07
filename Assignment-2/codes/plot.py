import matplotlib.pyplot as plt

# Function to read coordinates from a file
def read_coordinates(filename):
    x_coords = []
    y_coords = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(float, line.split())
            x_coords.append(x)
            y_coords.append(y)
    return x_coords, y_coords

# Read coordinates from file
x, y = read_coordinates('point.txt')

# Create a plot
plt.figure(figsize=(8, 6))
plt.plot(x, y, marker='o', linestyle='-', color='b')  # Draw points and lines between them
plt.title('Line Plot from Coordinates')
plt.xlabel('X axis')
plt.ylabel('Y axis')
plt.grid(True)
# Save the plot as a PNG file
plt.savefig('../figs/fig.png', format='png')
plt.show()

