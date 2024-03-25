import sys

# введення розміру квадратної матриці і перевірка на дійсність його
nRows = int(input("Введіть розмір квадратної матриці (не менше 4!): "))
if nRows < 3:
    print("Розмір матриці менше, ніж 4!!!")
    sys.exit()
arr = [[None for j in range(nRows)] for i in range(nRows)]

# введення символа заповнювача квадратної матриці і первірка на те, чи він 1
symbol = input("Введіть символ-заповнювач: ")
if len(symbol) != 1:
    print("Потрібно ввести лише один символ!")
    sys.exit()

# заповнення зубчастої матриці згідно варіанту
i = 1
while i < nRows - 1:
    if i == 1:
        j = 1
        while j < nRows - 1:
            arr[i][j] = symbol
            j += 1
    elif i == nRows - 2:
        j = 1
        while j < nRows - 1:
            arr[i][j] = symbol
            j += 1
    else:
        arr[i][1] = symbol
        arr[i][nRows - 2] = symbol
    i += 1

# дозаповнення пустих елементів зубчастої матриці для зручного виводу
i = 0
while i < nRows:
    j = 0
    while j < nRows:
        if arr[i][j] != symbol:
            arr[i][j] = " "
        j += 1
    i += 1

# вивід матриці
i = 0
while i < nRows:
    j = 0
    while j < nRows:
        print(arr[i][j], end=" ")
        j += 1
    print()
    i += 1