#include <iostream>

using namespace std;

// ����������� ������� ��� ������ � ���������
int** createEmptyMatrix(int rows, int cols);
void deleteMatrix(int** matrix, int rows);
int** multiplyMatrices(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2, int& countOperations);
void printMatrix(int** matrix, int rows, int cols);
void fillA(int** matrix, int rows, int cols);
void fillB(int** matrix, int rows, int cols);
int** localRecursiveAlgo(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2, int& countOperations);

int main() {
    // �������� ������ ������� � ������ ��������� ����������
    int n;
    while (true) {
        cout << "Enter n: ";
        cin >> n;
        if (n > 0) {
            break;
        }
        else {
            cout << "\"n\" must be greater or equals than 1. Try again." << endl;
        }
    }
    cout << endl;

    // ��������� � ���������� A
    int** A = createEmptyMatrix(n, n);
    cout << "Matrix A:" << endl;
    fillA(A, n, n);
    printMatrix(A, n, n);
    cout << endl;

    // ��������� � ���������� �
    int** B = createEmptyMatrix(n, n);
    cout << "Matrix B:" << endl;
    fillB(B, n, n);
    printMatrix(B, n, n);
    cout << endl;

    // ������ �������� � �� �
    cout << "With one-time assignment:" << endl;
    int countAll = 0;
    int** Y = multiplyMatrices(A, B, n, n, n, n, countAll);
    cout << "Matrix Y:" << endl;
    printMatrix(Y, n, n);
    cout << "Number of arithmetic operations: " << countAll << endl << endl;

    // ��������-����������� �������� ��������
    cout << "Local-recursive algorithm:" << endl;
    int countLocal = 0;
    int** Yl = localRecursiveAlgo(A, B, n, n, n, n, countLocal);
    cout << "Matrix Y:" << endl;
    printMatrix(Yl, n, n);
    cout << "Number of arithmetic operations: " << countLocal << endl << endl;



    deleteMatrix(A, n);
    deleteMatrix(B, n);
    deleteMatrix(Y, n);
    deleteMatrix(Yl, n);

    return 0;
}



// ������� ��� ��������� ����� ������� �������� ������
int** createEmptyMatrix(int rows, int cols) {
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

// ������� ��� ��������� ���'��, ������� ��������
void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// ������� ��� �������� ���� �������
int** multiplyMatrices(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2, int& countOperations) {
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
                countOperations += 2; // �� ���� �������� � ���� ���������
            }
            countOperations--; // �� ��������� �� ���������� �������� ������� ������� �����
        }
    }
    return resultMatrix;
}

// ������� ��� ������ ������� �� �����
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// ������� ��� ���������� ������� �
void fillA(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j <= i) {
                matrix[i][j] = cols - i + j;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
}

// ������� ��� ���������� ������� �
void fillB(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = 0;
        }
    }
    int mid = rows / 2 - 1, j = cols - 1, k1 = 0, k2 = rows;
    while (j != mid) {
        for (int i = k1; i < k2; i++) {
            matrix[i][j] = 1;
        }
        k1++;
        k2--;
        j--;
    }
}



int** localRecursiveAlgo(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2, int& countOperations) {
    if (cols1 != rows2) {
        cout << "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix." << endl;
        return nullptr;
    }
    int** resultMatrix = createEmptyMatrix(rows1, cols2);

    int mid = rows1 / 2 - 1, end = rows1 - 1, preEnd = end - 2;

    for (int i = 0; i < mid; i++) { // ��������� �� ������ �� �����ί ��������
        for (int j = end; j > preEnd; j--) { // ��������� �� ��������� ����� �� ������� ���������
            resultMatrix[i][j] = 0;
            for (int k = 0; k < rows1; k++) { // ���������� ����� ������� ������� ������� �Ѳ� ������Ҳ� ������� ����� �� ��������
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                countOperations += 2;
            }
            countOperations--;
        }
        for (int j = preEnd; j >= 0; j--) { // �� ����� �������� ����� ��������Ӫ��
            resultMatrix[i][j] = 0;
        }
        preEnd--;
    }
    for (int i = mid; i < cols1; i++) { // ��������� �� ������ ²� �����ί �������� � �� ʲ���
        for (int j = 0; j <= mid; j++) { // ����� �������� �������� ����� �����ߪ��
            resultMatrix[i][j] = 0;
        }
        for (int j = mid + 1; j < rows1; j++) { // ����� ��������
            resultMatrix[i][j] = 0;
            for (int k = 0; k < rows1; k++) { // ���������� ����� ������� ������� ������� �Ѳ� ������Ҳ� ������� ����� �� ��������
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
                countOperations += 2;
            }
            countOperations--;
        }
    }

    return resultMatrix;
}