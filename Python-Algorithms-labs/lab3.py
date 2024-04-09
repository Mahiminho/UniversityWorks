# МЕТОД ХОРД
import matplotlib.pyplot as plt
import numpy as np


x = 1.8

accuracy = 0.0001
a = 1.8
b = 2.3

def func(xt):
    return 3*xt - 14 + np.e**xt - np.e**(-xt)


func_first = 3 + np.e**x + np.e**(-x)
func_second = np.e**x + np.e**(-x)
real_x = 2.06922


if (func_first * func_second < 0):
    mass_f = [2.3]

    xn = mass_f[-1]
    n = xn - (func(xn) * (xn - a)) / (func(xn) - func(a))
    mass_f.append(n)

    while abs(mass_f[-1] - mass_f[-2]) > 0.0001:
        xn = mass_f[-1]
        n = xn - (func(xn) * (xn - a)) / (func(xn) - func(a))
        mass_f.append(n)

    print("Знаки першої і другої похідних є різними.")
    print("Масив значень х[n] до найближчого:")
    print(mass_f)
    print()

else:
    mass_f = [1.8]

    xn = mass_f[-1]
    n = xn - (func(xn) * (b - xn)) / (func(b) - func(xn))
    mass_f.append(n)

    while abs(mass_f[-1] - mass_f[-2]) > 0.0001:
        xn = mass_f[-1]
        n = xn - (func(xn) * (b - xn)) / (func(b) - func(xn))
        mass_f.append(n)

    print("Знаки першої і другої похідних є однаковими.")
    print("Масив значень х[n] до найближчого:")
    print(mass_f)
    print()

print("Корінь заданого рівняння 3*x - 14 + e^x - e^(-x) обрахований вручну: " + str(real_x))
print("Корінь заданого рівняння 3*x - 14 + e^x - e^(-x) методом хорд: " + str(mass_f[-1]))



# Графік заданої функції
xr = np.linspace(1.8, 2.3, 100)
yr = func(xr)

plt.plot(xr, yr)
plt.xlabel('x')
plt.ylabel('y')
plt.title('Графік функції 3*x - 14 + e^x - e^(-x)')
plt.grid(True)
plt.show()