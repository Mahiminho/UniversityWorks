import numpy as np
import matplotlib.pyplot as plt
import math

# ЗАВДАННЯ 1 (ІНТЕГРАЛЬНА КРИВА ФУНКЦІЇ З РАНЖОВАНИМИ ЗМІННИМИ)
start = 0.6
end = 1.4

x_num = []
y_num = []

for x in np.arange(start, end, 0.001):
    y = np.cos(x) * x * x
    y = -2 * np.sin(x) + 2 * x * np.cos(x) + x * x * np.sin(x)
    x_num.append(x)
    y_num.append(y)


plt.plot(x_num, y_num)
plt.xlabel('x')
plt.ylabel('y')
plt.title('y = x^2 * cos(x)')
plt.grid()
plt.show()



# ЗАВДАННЯ 2 (ПЛОЩА ПІД КРИВОЮ ГРАФІКА ФУНКЦІЇ ЗА МЕТОДОМ ПРЯМОКУТНИКІВ)
start = 0.6
end = 1.4
n = 1000

h = (end - start) / n

s = 0
x = start

for i in range(n):
    x += h
    y = math.cos(x) * x * x
    s += h * y

print("Площа під кривою графіка функції за методом прямокутників: " + str(s))



# ЗАВДАННЯ 3 (ПЛОЩА ПІД КРИВОЮ ГРАФІКА ФУНКЦІЇ ЗА ФОРМУЛОЮ СІМПСОНА)
start = 0.6
end = 1.4
n = 1000
h = (end - start) / (n - 1)
x = np.linspace(start, end, n)

f = np.cos(x) * x * x

s_simpson = (h / 3) * (f[0] + 2 * sum(f[:n - 2:2]) + 4 * sum(f[1:n - 1:2]) + f[n - 1])

print("Площа під кривою графіка функції за методом прямокутників: " + str(s_simpson))