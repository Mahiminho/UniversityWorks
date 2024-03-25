#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

// моя функція до 18ого варіанту


void func(int** arr, int n) {
    int w = n / 6;
    // Верхні рядки
    for (int l = 0; l < w; l++)
        for (int r = 0; r < n; r++)
            arr[l][r] = 0;
    // Нижні рядки
    for (int l = n - w; l < n; l++)
        for (int r = 0; r < n; r++)
            arr[l][r] = 0;
    // Центральний квадрат
    for (int l = 2 * w; l < n - 2 * w; l++)
        for (int r = 2 * w; r < n - 2 * w; r++)
            arr[l][r] = 0;
    // Ліві рядки
    for (int r = 0; r < w; r++)
        for (int l = w; l < n - w; l++)
            arr[l][r] = 0;
    // Праві рядки
    for (int r = n - w; r < n; r++)
        for (int l = w; l < n - w; l++)
            arr[l][r] = 0;
}

int main()
{
    int** arr, n;
    cout << "Enter order of matrix: ";
    cin >> n;
    cout << "-----------------------------------------------------" << endl;

    if (n % 6 != 0)
    {
        cout << "Incorrect matrix size!" << endl;
        return 1;
    }

    arr = new int* [n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
        for (int j = 0; j < n; j++)
            arr[i][j] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(3) << arr[i][j];
        cout << endl;
    }

    func(arr, n);

    cout << "-----------------------------------------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(3) << arr[i][j];
        cout << endl;
    }

    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;

    return 0;
}