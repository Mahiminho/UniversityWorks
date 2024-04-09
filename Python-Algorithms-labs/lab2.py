# Обчислення інтегралу методом Гауса для 5-ти вузлів
import math

a = 0
b = math.pi/2
t = [0.90617985, 0.53846931, 0.0, -0.53846931, -0.90617985]
A = [0.23692689, 0.47862867, 0.56888889, 0.47862867, 0.23692689]
result = 0


for i in range(5):
    x = ((b - a) * t[i] + b + a) / 2
    f = math.sqrt(1 - 0.5 * (math.sin(x) ** 2))
    result += A[i] * f

result = ((b - a) / 2) * result

print("Значення інтегралу: " + str(result))

# Побудова графіка для функції
import numpy as np
import matplotlib.pyplot as plt

start = a
end = b

x_num = []
y_num = []

for x in np.arange(start, end, 0.001):
    y = math.sqrt(1 - 0.5 * (math.sin(x)**2))
    x_num.append(x)
    y_num.append(y)

plt.plot(x_num, y_num)
plt.xlabel('x')
plt.ylabel('y')
plt.title('y = √(1 - 0.5 * sin(x)^2)')
plt.grid()
plt.show()