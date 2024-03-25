#include <iostream>
#include <ctime>
#include <iomanip>
#include "matrix.h"
#pragma once

using namespace std;

int main() {
	// матриц€, розм≥р €коњ створений за замовчуванн€м (10 р€дк≥в на 5 стовпц≥в)
	Matrix<int> m;
	m.return_matrix();
	m.longest_row();
	cout << endl;
	//матриц€, розм≥р €коњ задаЇ користувач
	int irow, icol;
    cout << "Number of row: " << endl;
	cin >> irow;
	cout << "Number of col: " << endl;
	cin >> icol;
	Matrix<int> m2(irow, icol);
	m2.return_matrix();
	m2.longest_row();

	return 0;
}

/*
//srand((unsigned int)time(NULL));
int a = rand() % 201 - 100;
int b = rand() % 201 - 100;
int c = rand() % 201 - 100;
int d = rand() % 201 - 100;
int e = rand() % 201 - 100;

cout << a << endl;
cout << b << endl;
cout << c << endl;
cout << d << endl;
cout << e << endl;
*/