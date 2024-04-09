import numpy as np
import matplotlib.pyplot as plt

# МЕТОД ПОКООРДИНАТНОГО СХОДЖЕННЯ З ПОСТІЙНИМ КРОКОМ
def func(x, y):
    return np.e**(-x) + (x + y**2)**2

a, b, c, d = -2, 2, -3, 3
accuracy = 10**(-5)
step = 0.001

# Ми починаємо з точки x, y = -2, -3
n_a = func(a - step, c)
n_b = func(a + step, c)
n_c = func(a, c - step)
n_d = func(a, c + step)

n_n = min(n_a, n_b, n_c, n_d) # перший рух вийшов по Y вверх
mass = [57]

mass_x = []
mass_y = []

if n_n == n_a:
    a -= step
    mass.append(n_a)
elif n_n == n_b:
    a += step
    mass.append(n_b)
elif n_n == n_c:
    c -= step
    mass.append(n_c)
else:
    c += step
    mass.append(n_d)

mass_x.append(a)
mass_y.append(c)

while abs(mass[-2] - mass[-1]) >= accuracy:
    n_a = func(a - step, c)
    n_b = func(a + step, c)
    n_c = func(a, c - step)
    n_d = func(a, c + step)

    n_n = min(n_a, n_b, n_c, n_d)

    if n_n == n_a:
        a -= step
        mass.append(n_a)
    elif n_n == n_b:
        a += step
        mass.append(n_b)
    elif n_n == n_c:
        c -= step
        mass.append(n_c)
    else:
        c += step
        mass.append(n_d)

    mass_x.append(a)
    mass_y.append(c)


n = len(mass)
mass_len = [i for i in range(n)]


print("Точка мінімуму X: " + str(round(a, 5)))
print("Точка мінімуму Y: " + str(round(c, 5)))
print("Точка мінімуму Z: " + str(round(mass[-1], 5)))
print()
print("Масив спуску по Z: " + str(mass))



XY, ax = plt.subplots()
ax.plot(mass_x, mass_y, label='X, Y') # тобто вигляд на площину XY
ax.set_xlim([-2, 2])
ax.set_ylim([-3, 3])
plt.xlabel('Зміна X')
plt.ylabel('Зміна Y')
ax.set_title('Графік сходження (вигляд зверху)')
ax.grid(True)
ax.legend()
plt.show()



Z, ax = plt.subplots()
ax.plot(mass_len, mass, label='Z, nZ') # тобто вигляд на площину Z
plt.xlabel('К-сть точок Z')
plt.ylabel('Зміна Z')
ax.set_title('Графік сходження (вигляд збоку)')
ax.grid(True)
ax.legend()
plt.show()



nx = np.linspace(-2, 2, 100)
ny = np.linspace(-3, 3, 100)
nX, nY = np.meshgrid(nx, ny)
nZ = np.exp(-nX) + (nX + nY**2)**2

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot_surface(nX, nY, nZ, cmap='viridis')
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D графік функції $f(x, y) = e^{-x} + (x + y^2)^2$')
plt.show()