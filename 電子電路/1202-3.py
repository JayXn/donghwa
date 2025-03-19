import numpy as np
import matplotlib.pyplot as plt

theta = np.linspace(0, 2 * np.pi, 100) 
x = np.cos(theta)  
y = np.sin(theta)  

plt.plot(x, y)
plt.gca().set_aspect('equal', adjustable='box')  
plt.show()
