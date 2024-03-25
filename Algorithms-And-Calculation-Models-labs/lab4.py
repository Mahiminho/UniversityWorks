from tabulate import tabulate

# Метод Ейлера
x = [0]
y = [1]
h = 0.1

i = 0
while x[-1] <= 1:
    f = (y[-1] / (x[-1] + 1)) - y[-1]**2
    xn = x[-1] + h
    yn = y[-1] + h * f

    x.append(round(xn, 1))
    y.append(round(yn, 5))

x.pop()
y.pop()
print("Чисельний розв’язок задачі Коші методом Ейлера:")
table = [x, y]
print(tabulate(table, headers='firstrow', tablefmt='fancy_grid'))
print()






# Модифікований метод Ейлера
x = [0]
y = [1]
h = 0.1

i = 0
while x[-1] <= 1:
    f = (y[-1] / (x[-1] + 1)) - y[-1]**2
    xn = x[-1] + h
    i_yn = y[-1] + h * f
    i_f = (i_yn / (xn + 1)) - i_yn**2
    yn = y[-1] + h * ((f + i_f) / 2)

    x.append(round(xn, 1))
    y.append(round(yn, 5))

x.pop()
y.pop()
print("Чисельний розв’язок задачі Коші модифікованим методом Ейлера:")
table = [x, y]
print(tabulate(table, headers='firstrow', tablefmt='fancy_grid'))
print()







# Метод Рунге-Кутта
x = [0]
y = [1]
h = 0.1

i = 0
while x[-1] <= 1:
    Ki1 = (y[-1] / (x[-1] + 1)) - y[-1]**2

    xn = x[-1] + h / 2
    p_yn = y[-1] + (h / 2) * Ki1
    Ki2 = (p_yn / (xn + 1)) - p_yn ** 2

    xn = xn + h / 2
    p_yn = p_yn + (h / 2) * Ki2
    Ki3 = (p_yn / (xn + 1)) - p_yn ** 2

    xn = xn + h
    p_yn = p_yn + h * Ki3
    Ki4 = (p_yn / (xn + 1)) - p_yn ** 2

    d_yn = (h / 6) * (Ki1 + Ki2 + Ki3 + Ki4)
    yn = y[-1] + d_yn

    xn = x[-1] + h



    x.append(round(xn, 1))
    y.append(round(yn, 5))

x.pop()
y.pop()
print("Чисельний розв’язок задачі Коші методом Рунге-Кутта:")
table = [x, y]
print(tabulate(table, headers='firstrow', tablefmt='fancy_grid'))
print()