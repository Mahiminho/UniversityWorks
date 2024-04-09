#include <iostream>
#include <chrono>

using namespace std;

const int N1 = 217;
const int N2 = 149;
const int N3 = 100;

int** createEmptyMatrix(int rows, int cols) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; ++i) {
		matrix[i] = new int[cols];
	}
	return matrix;
}

int** multiplyMatrices(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2) {
	if (cols1 != rows2) {
		cout << "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix." << endl;
			return nullptr;
	}
	int** resultMatrix = createEmptyMatrix(rows1, cols2);
	for (int i = 0; i < rows1; ++i) {
		for (int j = 0; j < cols2; ++j) {
			resultMatrix[i][j] = 0;
			for (int k = 0; k < cols1; ++k) {
				resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return resultMatrix;
}

void printMatrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void deleteMatrix(int** matrix, int rows) {
	for (int i = 0; i < rows; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}



int main() {
	srand(time(NULL));
	int** matrixA = createEmptyMatrix(N1, N2);
	int** matrixB = createEmptyMatrix(N2, N3);

	// fill A
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			matrixA[i][j] = rand() % 9999 + 100;
		}
	}

	// fill B
	for (int i = 0; i < N2; i++) {
		for (int j = 0; j < N3; j++) {
			matrixB[i][j] = rand() % 9999 + 100;
		}
	}

	auto start = chrono::high_resolution_clock::now();
	int** matrixR = multiplyMatrices(matrixA, matrixB, N1, N2, N2, N3);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - start);
	int time = duration.count();

	printMatrix(matrixR, N1, N3);
	cout << "\nTIME: " << time << " ms." << endl;


	return 0;
}