import numpy as np
import matplotlib.pyplot as plt

t1 = np.linspace(0, 5, 500)    
t2 = np.linspace(5, 10, 500)   
t3 = np.linspace(10, 12, 200)  

v1 = (3/8) * t1**2
v2 = (75/8) - (10/4)*(t2 - 5)
v3 = -25/8  

t = np.concatenate([t1, t2, t3])
v = np.concatenate([v1, v2, v3 * np.ones_like(t3)])  

plt.plot(t1, v1, '*', color='blue', label='0 ≤ t ≤ 5')  
plt.plot(t2, v2, '*', color='orange', label='5 < t ≤ 10') 
plt.plot(t3, v3 * np.ones_like(t3), '*', color='green', label='10 < t ≤ 12')  

plt.grid(True)

plt.show()
