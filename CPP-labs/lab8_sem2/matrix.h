#pragma once
// matrix.h
#ifndef matrix_h__
#define matrix_h__
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;


template<class T>
class Matrix 
{
private:
	int row;
	int col;
	T** Matr;
public:

	// конструктор за замовчуванням
	Matrix();
	// конструктор з параметрами
	Matrix(int x, int y);
	// конструктор копіюванням
	Matrix(const Matrix& init);
	// деструктор
	~Matrix();
	//перевантаження оператора виводу
	void return_matrix();
	// рядок з найдовшим чергуванням знаків
	void longest_row();
};

//конструктор за замовчуванням
template <class T>
Matrix<T>::Matrix()
{
	row = 10;
	col = 5;
	Matr = new T * [row];
	for (int i = 0; i < row; i++)
	{
		Matr[i] = new T[col];
		for (int j = 0; j < col; j++)
		{
			Matr[i][j] = rand() % 201 - 100;
		}

	}
}

// конструктор з параметрами
template <class T>
Matrix<T>::Matrix(int x, int y)
{
	row = x;
	col = y;
	Matr = new T * [row];
	for (int i = 0; i < row; i++)
	{
		Matr[i] = new T[col];
		for (int j = 0; j < col; j++)
		{
			Matr[i][j] = rand() % 201 - 100;
		}
	}
}

//контруктор копіюванням
template<class T>
Matrix<T>::Matrix(const Matrix<T>& init)
{
	if (&Matr != 0)
	{
		for (int j = 0; j < row; j++)
		{
			delete Matr[j];
		}
		delete[] Matr;
	}
	row = init.row;
	col = init.col;
	Matr = new T * [row];
	for (int i = 0; i < row; i++)
	{
		Matr[i] = new T[col];
		for (int j = 0; j < col; j++)
		{
			Matr[i][j] = 0;
		}
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			Matr[i][j] = init.Matr[i][j];
		}
}

//деструктор
template<class T>
Matrix<T>::~Matrix()
{
	for (int j = 0; j < row; j++)
	{
		delete Matr[j];
	}
	delete[] Matr;
}

template <class T>
void Matrix<T>::return_matrix()
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << Matr[i][j] << " " << "\t";
		}
		cout << endl;
	}
	cout << endl;
}


template<class T>
void Matrix<T>::longest_row()
{
	int count = 0, max_count = 0, search_row;
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c += 1)
			if (c + 1 < col)
				if (
					(Matr[r][c] < 0 && Matr[r][c + 1] >= 0) ||
					(Matr[r][c] >= 0 && Matr[r][c + 1] < 0)
					)
				{
					count++;
					if (count > max_count)
					{
						max_count = count;
						search_row = r;
					}
				}
		count = 0;
	}

	cout << "Max: " << max_count << endl;
	cout << "Search row: " << search_row << endl;



}

#endif // matrix_h__


/*
int count_num = 0; // лічильник чисел з різними знаками
for (int i = 0; i < row; i++)
	for (int j = 0; j < col; j++)
	{
		//while (row < j)
		//{
			if ((Matr[i][j] <= 0 && Matr[i][j + 1] >= 0) || (Matr[i][j] >= 0 && Matr[i][j + 1] <= 0))
			{
				count_num++;
			}
		//}
		//int ret =
	}
cout << "The line number with the longest series of elements in which the characters alternate: " << count_num << endl;
return count_null;
*/