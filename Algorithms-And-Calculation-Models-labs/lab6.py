import matplotlib.pyplot as plt
import numpy as np
import math

x = [0, 0.22, 0.44, 0.67, 0.89, 1.11, 1.33, 1.56, 1.78, 2]
y = [0.09, 0.15, 0.05, 0.49, 0.69, 1.1, 1.91, 2.45, 3.15, 3.56]


# Лінійний
S_xx = 0
S_x = 0
S_y = 0
S_xy = 0
n = len(x)
for i in range(n):
    S_xx += x[i] ** 2
    S_x += x[i]
    S_y += y[i]
    S_xy += x[i] * y[i]

delta = (n + 1) * S_xx - S_x ** 2
delta_a = (n + 1) * S_xy - S_x * S_y
delta_b = S_xx * S_y - S_x * S_xy

a0 = delta_a / delta
b0 = delta_b / delta

x_p = np.linspace(0, 2, 10)

def f(x_p):
    return a0 * x_p + b0

y_p = f(x_p)


# Квадратичний
n = len(x)
k_0 = n + 1
k_1_4 = []
for power in range(1, 5, 1):
    k = 0
    for i in range(n):
        k += x[i] ** power
    k_1_4.append(k)
k_y = 0
k_xy = 0
k_x2y = 0
for i in range(n):
    k_y += y[i]
    k_xy += x[i] * y[i]
    k_x2y += x[i] ** 2 * y[i]


before_equal_sign = np.array([[k_0, k_1_4[0], k_1_4[1]], [k_1_4[0], k_1_4[1], k_1_4[2]], [k_1_4[1], k_1_4[2], k_1_4[3]]])
after_equal_sign = np.array([k_y, k_xy, k_x2y])
results = np.linalg.solve(before_equal_sign, after_equal_sign)
a1 = results[2]
b1 = results[1]
c1 = results[0]


x_t = np.linspace(0, 2, 20)

def f(x_t):
    return a1 * x_t ** 2 + b1 * x_t + c1

y_t = f(x_t)


# y = a * x^b
S_xx1 = 0
S_x1 = 0
S_y1 = 0
S_xy1 = 0
n1 = len(x)
for i in range(n1):
    S_xx1 += x[i] ** 2
    S_x1 += x[i]
    S_y1 += np.log(y[i])
    S_xy1 += x[i] * np.log(y[i])

delta1 = n1 * S_xx1 - S_x1 ** 2
delta_a1 = n1 * S_xy1 - S_x1 * S_y1
delta_b1 = S_xx1 * S_y1 - S_x1 * S_xy1

A = delta_a1 / delta1
B = delta_b1 / delta1

a2 = math.e**B
b2 = math.e**A

x_e = np.linspace(0, 2, 20)

def f(x_c):
    return a2 * b2**x_c

y_v = f(x_e)



fig, ax = plt.subplots()
ax.plot(x, y, label='Графік по точках')
ax.plot(x_p, y_p, label='Графік лін. емп. функ')
ax.plot(x_t, y_t, label='Графік квадр. емп. функ')
ax.plot(x_e, y_v, label='Графік y = a*x^b')
ax.legend()
plt.show()



# Для обчислення похибок
x = [0, 0.22, 0.44, 0.67, 0.89, 1.11, 1.33, 1.56, 1.78, 2]
y = [0.09, 0.15, 0.05, 0.49, 0.69, 1.1, 1.91, 2.45, 3.15, 3.56]
y1 = [] # лінійні значення
y2 = [] # квадратичні значення
y3 = [] # значення по заданій формулі

n = len(x)
for i in range(n):
    y1.append(round(a0 * x[i] + b0, 5))
    y2.append(round(a1 * x[i] ** 2 + b1 * x[i] + c1, 5))
    y3.append(round(a2 * b2**x[i], 5))


print("Масив заданих значень: " + str(y))
print()
print("Масив значень для лінійної апроксимації: " + str(y1))
print("Масив значень для квадратичної апроксимації: " + str(y2))
print("Масив значень для апроксимації за формулою: " + str(y3))


# Для абсолютних похибок
y_dis1 = []
y_dis2 = []
y_dis3 = []

for i in range(n):
    y_dis1.append(round(y[i] - y1[i], 5))
    y_dis2.append(round(y[i] - y2[i], 5))
    y_dis3.append(round(y[i] - y3[i], 5))

print()
print("Масив похибок в точках для лінійної апроксимації: " + str(y_dis1))
print("Масив похибок в точках для квадратичної апроксимації: " + str(y_dis2))
print("Масив похибок в точках для апроксимації за функцією: " + str(y_dis3))

print()
print("Середня абсолютна похибка для лінійної апроксимації: " + str(np.mean(y_dis1)))
print("Середня абсолютна похибка для квадратичної апроксимації: " + str(np.mean(y_dis2)))
print("Середня абсолютна похибка для апроксимації за функцією: " + str(np.mean(y_dis3)))


# Для відносних похибок
y_div1 = []
y_div2 = []
y_div3 = []

for i in range(n):
    y_div1.append(round(abs((y_dis1[i] / y[i]) * 100), 5))
    y_div2.append(round(abs((y_dis2[i] / y[i]) * 100), 5))
    y_div3.append(round(abs((y_dis3[i] / y[i]) * 100), 5))

print()
print("Масив відносних похибок в точках для лінійної апроксимації: " + str(y_div1))
print("Масив відносних похибок в точках для квадратичної апроксимації: " + str(y_div2))
print("Масив відносних похибок в точках для апроксимації за функцією: " + str(y_div3))

print()
print("Середня відносна похибка для лінійної апроксимації: " + str(np.mean(y_div1)))
print("Середня відносна похибка для квадратичної апроксимації: " + str(np.mean(y_div2)))
print("Середня відносна похибка для апроксимації за функцією: " + str(np.mean(y_div3)))
