import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def lorenz_system(x, y, z):
    """Define the Lorenz system equations"""
    s = 10    # Prandtl number
    r = 28    # Rayleigh number
    b = 8/3   # Geometric factor
    
    dx = -s * (x - y)
    dy = -x * z + r * x - y
    dz = x * y - b * z
    
    return dx, dy, dz

def euler_integration(x0, y0, z0, t_min, t_max, h=0.001):
    """Perform Euler integration of the Lorenz system"""
    t = np.arange(t_min, t_max + h, h)
    n = len(t)
    
    # Initialize arrays
    x = np.zeros(n)
    y = np.zeros(n)
    z = np.zeros(n)
    
    # Set initial conditions
    x[0], y[0], z[0] = x0, y0, z0
    
    # Euler integration
    for i in range(n - 1):
        dx, dy, dz = lorenz_system(x[i], y[i], z[i])
        x[i+1] = x[i] + h * dx
        y[i+1] = y[i] + h * dy
        z[i+1] = z[i] + h * dz
    
    return x, y, z, t

# Parameters and initial conditions
h = 0.001
x0, y0, z0 = 10, 10, 10
t_min, t_max, t_mid = 0, 30, 15

# Full simulation (t = 0 to 30)
x, y, z, t = euler_integration(x0, y0, z0, t_min, t_max)

# Plot time series
plt.figure(figsize=(10, 5))
plt.plot(t, x, label='x(t)')
plt.plot(t, y, label='y(t)')
plt.plot(t, z, label='z(t)')
plt.legend()
plt.xlabel('t')
plt.title('Explicit Euler for time t = 0 to t=30')
plt.grid(True)
plt.show()

# Plot 3D trajectory
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.plot(x, y, z, 'k', linewidth=0.5)
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')
ax.set_title('3D plot for t = 0 to t=30')
plt.show()

# Plot 2D projections
plt.figure(figsize=(8, 6))
plt.subplot(2, 1, 1)
plt.plot(x, z, 'k')
plt.xlabel('x')
plt.ylabel('z')
plt.title('x-z projection')
plt.grid(True)

plt.subplot(2, 1, 2)
plt.plot(y, z, 'k')
plt.xlabel('y')
plt.ylabel('z')
plt.title('y-z projection')
plt.grid(True)

plt.tight_layout()
plt.show()

# Split simulation (t = 0-15 and 15-30)
# First half (t = 0 to 15)
x1, y1, z1, t1 = euler_integration(x0, y0, z0, t_min, t_mid)

plt.figure(figsize=(10, 5))
plt.plot(t1, x1, label='x(t)')
plt.plot(t1, y1, label='y(t)')
plt.plot(t1, z1, label='z(t)')
plt.legend()
plt.xlabel('t')
plt.title("Euler's method, t = 0 to 15")
plt.grid(True)
plt.show()

# Second half (t = 15 to 30)
x2, y2, z2, t2 = euler_integration(x1[-1], y1[-1], z1[-1], t_mid, t_max)

plt.figure(figsize=(10, 5))
plt.plot(t2, x2, label='x(t)')
plt.plot(t2, y2, label='y(t)')
plt.plot(t2, z2, label='z(t)')
plt.legend()
plt.xlabel('t')
plt.title("Euler's method, t = 15 to 30")
plt.grid(True)
plt.show()
