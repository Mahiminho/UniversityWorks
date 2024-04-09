#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <chrono>
#include "mpi.h"

using namespace std;

// ініціалізація функцій для роботи з матрицями
double** createEmptyMatrix(int rows, int cols);
void deleteMatrix(double** matrix, int rows);
void fillMatrix(double** matrix, int rows, int cols);
void fillMatrixRandom(double** matrix, int rows, int cols);
void chooseTypeFill(double** matrix, int rows, int cols);
double** multiplyMatrices(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2);
void multiplyMatrixByScalar(double** matrix, int rows, int cols, int scalar);
double** addMatrices(double** matrix1, double** matrix2, int rows, int cols);
double** transposeMatrix(double** matrix, int rows, int cols);
double determinant(double** matrix, int n);
void printMatrix(double** matrix, int rows, int cols);
string matrixToString(double** matrix, int rows, int cols);
void appendMatrixToFile(double** matrix, int rows, int cols, ofstream &outputFile);
double* convertTo1D(double** array, int rows, int cols);
double** convertTo2D(double* array, int rows, int cols);
double* allocateMemoryFor1DArray(int size);



int main(int argc, char** argv) {
    // MPI
    int numtasks, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);



    if (rank == 0) {
        // введення розміру матриць і вибору отримання результатів
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
        int choice;
        while (true) {
            cout << "\nEnter 1 to write all data to file or 2 to print on screen: ";
            cin >> choice;
            if (choice == 1 || choice == 2) {
                break;
            }
            else {
                cout << "Enter correct choice!" << endl;
            }
        }
        cout << endl;



        // створення і заповнення A КОРИСТУВАЧЕМ
        double** A = createEmptyMatrix(n, n);
        cout << "Matrix A (n * n)" << endl;
        chooseTypeFill(A, n, n);

        // створення і заповнення A1 КОРИСТУВАЧЕМ
        double** A1 = createEmptyMatrix(n, n);
        cout << "Matrix A1 (n * n)" << endl;
        chooseTypeFill(A1, n, n);

        // створення і заповнення b1 КОРИСТУВАЧЕМ
        double** b1 = createEmptyMatrix(n, 1);
        cout << "Matrix b1 (n * 1)" << endl;
        chooseTypeFill(b1, n, 1);

        // створення і заповнення c1 КОРИСТУВАЧЕМ
        double** c1 = createEmptyMatrix(n, 1);
        cout << "Matrix c1 (n * 1)" << endl;
        chooseTypeFill(c1, n, 1);

        // створення і заповнення A2 КОРИСТУВАЧЕМ
        double** A2 = createEmptyMatrix(n, n);
        cout << "Matrix A2 (n * n)" << endl;
        chooseTypeFill(A2, n, n);

        // створення і заповнення B2 КОРИСТУВАЧЕМ
        double** B2 = createEmptyMatrix(n, n);
        cout << "Matrix B2 (n * n)" << endl;
        chooseTypeFill(B2, n, n);



        // таймер старт
        auto start = chrono::high_resolution_clock::now();
        


        // надсилання розміру і вибору виводу процесу 1
        MPI_Send(&n, 1, MPI_INT, 1, 10, MPI_COMM_WORLD);
        MPI_Send(&choice, 1, MPI_INT, 1, 11, MPI_COMM_WORLD);

        // надсилання даних процесу 1
        double* A1_send = convertTo1D(A1, n, n);
        double* b1_send = convertTo1D(b1, n, 1);
        double* c1_send = convertTo1D(c1, n, 1);
        MPI_Send(A1_send, n * n, MPI_DOUBLE, 1, 201, MPI_COMM_WORLD);
        MPI_Send(b1_send, n * 1, MPI_DOUBLE, 1, 202, MPI_COMM_WORLD);
        MPI_Send(c1_send, n * 1, MPI_DOUBLE, 1, 203, MPI_COMM_WORLD);
        // надсилання даних процесу 2
        double* A2_send = convertTo1D(A2, n, n);
        double* B2_send = convertTo1D(B2, n, n);
        MPI_Send(A2_send, n * n, MPI_DOUBLE, 2, 207, MPI_COMM_WORLD);
        MPI_Send(B2_send, n * n, MPI_DOUBLE, 2, 208, MPI_COMM_WORLD);
        


        // стоврення і заповнення b ПО ЗАМОВЧУВАННЮ
        double** b = createEmptyMatrix(n, 1);
        for (int i = 1; i <= n; i++) {
            b[i - 1][0] = 16 / (i * i * i);
        }

        // обрахунок y1 = A * b
        double** y1 = multiplyMatrices(A, b, n, n, n, 1);



        // обрахунки x
        double* y2_recv = allocateMemoryFor1DArray(n * 1);
        MPI_Recv(y2_recv, n * 1, MPI_DOUBLE, 1, 301, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** y2 = convertTo2D(y2_recv, n, 1);
        double** y1Ty2 = multiplyMatrices(transposeMatrix(y1, n, 1), y2, 1, n, n, 1);

        double* Y3_recv = allocateMemoryFor1DArray(n * n);
        MPI_Recv(Y3_recv, n * n, MPI_DOUBLE, 2, 302, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** Y3 = convertTo2D(Y3_recv, n, n);
        double** Y3y1 = multiplyMatrices(Y3, y1, n, n, n, 1);

        double* Y3Y3y2_recv = allocateMemoryFor1DArray(n * 1);
        MPI_Recv(Y3Y3y2_recv, n * 1, MPI_DOUBLE, 2, 303, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** Y3Y3y2 = convertTo2D(Y3Y3y2_recv, n, 1);
        double** Y3Y3y2_plus_Y3y1 = addMatrices(Y3Y3y2, Y3y1, n, 1);

        double* Y3y2_plus_y2_T_recv = allocateMemoryFor1DArray(1 * n);
        MPI_Recv(Y3y2_plus_y2_T_recv, 1 * n, MPI_DOUBLE, 1, 304, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** Y3y2_plus_y2_T = convertTo2D(Y3y2_plus_y2_T_recv, 1, n);
        double** firstPart = multiplyMatrices(Y3y2_plus_y2_T, Y3Y3y2_plus_Y3y1, 1, n, n, 1);
        
        double x = determinant(addMatrices(y1Ty2, firstPart, 1, 1), 1);
        


        // таймер стоп
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::milliseconds>(end - start);
        int time = duration.count();



        // типи виводу
        if (choice == 1) {
            // створення файлу і запис в нього
            ofstream outputFile1("Processor1.txt", ios::app);
            outputFile1 << "<=== PROCESSOR 1 ===>" << endl << endl;
            outputFile1 << "A:" << endl;
            appendMatrixToFile(A, n, n, outputFile1);
            outputFile1 << endl;
            outputFile1 << "b:" << endl;
            appendMatrixToFile(b, n, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "y1:" << endl;
            appendMatrixToFile(y1, n, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "y1Ty2:" << endl;
            appendMatrixToFile(y1Ty2, 1, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "Y3y1:" << endl;
            appendMatrixToFile(Y3y1, n, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "Y3Y3y2_plus_Y3y1:" << endl;
            appendMatrixToFile(Y3Y3y2_plus_Y3y1, n, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "firstPart:" << endl;
            appendMatrixToFile(firstPart, 1, 1, outputFile1);
            outputFile1 << endl;
            outputFile1 << "x: " << x << endl;
            outputFile1 << endl;
            outputFile1 << "TIME: " << time << " milliseconds" << endl;
            outputFile1 << endl;
            outputFile1.close();
        }
        else if (choice == 2) {
            cout << "<=== PROCESSOR 1 ===>" << endl << endl
                << "A:" << endl << matrixToString(A, n, n) << endl
                << "b:" << endl << matrixToString(b, n, 1) << endl
                << "y1:" << endl << matrixToString(y1, n, 1) << endl
                << "y1Ty2:" << endl << matrixToString(y1Ty2, 1, 1) << endl
                << "Y3y1:" << endl << matrixToString(Y3y1, n, 1) << endl
                << "Y3Y3y2_plus_Y3y1:" << endl << matrixToString(Y3Y3y2_plus_Y3y1, n, 1) << endl
                << "firstPart:" << endl << matrixToString(firstPart, 1, 1) << endl
                << "x: " << x << endl
                << "TIME: " << time << " milliseconds" << endl << endl;

            int signal = 1;
            MPI_Send(&signal, 1, MPI_INT, 1, 901, MPI_COMM_WORLD);
        }
        

        
        // очищення памяті
        deleteMatrix(b, n);
        deleteMatrix(A, n);
        deleteMatrix(y1, n);

        deleteMatrix(A1, n);
        deleteMatrix(b1, n);
        deleteMatrix(c1, n);
        deleteMatrix(A2, n);
        deleteMatrix(B2, n);

        deleteMatrix(y2, n);
        deleteMatrix(y1Ty2, 1);
        deleteMatrix(Y3, n);
        deleteMatrix(Y3y1, n);
        deleteMatrix(Y3Y3y2, n);
        deleteMatrix(Y3Y3y2_plus_Y3y1, n);
        deleteMatrix(Y3y2_plus_y2_T, 1);
        deleteMatrix(firstPart, 1);

        delete[] A1_send;
        delete[] b1_send;
        delete[] c1_send;
        delete[] A2_send;
        delete[] B2_send;
        delete[] Y3_recv;
        delete[] y2_recv;
        delete[] Y3Y3y2_recv;
        delete[] Y3y2_plus_y2_T_recv;
    }
    else if (rank == 1) {
        // отримання розміру та вибору
        int n, choice;
        MPI_Recv(&n, 1, MPI_INT, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&choice, 1, MPI_INT, 0, 11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // отримання робочих матриць
        double* A1_recv = allocateMemoryFor1DArray(n * n);
        double* b1_recv = allocateMemoryFor1DArray(n * 1);
        double* c1_recv = allocateMemoryFor1DArray(n * 1);

        MPI_Recv(A1_recv, n * n, MPI_DOUBLE, 0, 201, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(b1_recv, n * 1, MPI_DOUBLE, 0, 202, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(c1_recv, n * 1, MPI_DOUBLE, 0, 203, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double** A1 = convertTo2D(A1_recv, n, n);
        double** b1 = convertTo2D(b1_recv, n, 1);
        double** c1 = convertTo2D(c1_recv, n, 1);

        // надсилання розміру і вибору процесу 2
        MPI_Send(&n, 1, MPI_INT, 2, 12, MPI_COMM_WORLD);
        MPI_Send(&choice, 1, MPI_INT, 2, 13, MPI_COMM_WORLD);



        // обрахунок y2 = A1 * (b1 + 16 * c1)
        multiplyMatrixByScalar(c1, n, 1, 16);
        double** b1_plus_c1 = addMatrices(b1, c1, n, 1);
        double** y2 = multiplyMatrices(A1, b1_plus_c1, n, n, n, 1);



        // розсилка y2
        double* y2_send1 = convertTo1D(y2, n, 1);
        MPI_Send(y2_send1, n * 1, MPI_DOUBLE, 0, 301, MPI_COMM_WORLD);
        double* y2_send2 = convertTo1D(y2, n, 1);
        MPI_Send(y2_send2, n * 1, MPI_DOUBLE, 2, 315, MPI_COMM_WORLD);

        // обрахунки x
        double* Y3y2_recv = allocateMemoryFor1DArray(n * 1);
        MPI_Recv(Y3y2_recv, n * 1, MPI_DOUBLE, 2, 310, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** Y3y2 = convertTo2D(Y3y2_recv, n, 1);
        double** Y3y2_plus_y2_T = transposeMatrix(addMatrices(Y3y2, y2, n, 1), n, 1);

        double* Y3y2_plus_y2_T_send = convertTo1D(Y3y2_plus_y2_T, 1, n);
        MPI_Send(Y3y2_plus_y2_T_send, 1 * n, MPI_DOUBLE, 0, 304, MPI_COMM_WORLD);



        // типи виводу
        if (choice == 1) {
            // створення і запис у файл
            ofstream outputFile2("Processor2.txt", ios::app);
            outputFile2 << "<=== PROCESSOR 2 ===>" << endl << endl;
            outputFile2 << "A1:" << endl;
            appendMatrixToFile(A1, n, n, outputFile2);
            outputFile2 << endl;
            outputFile2 << "b1:" << endl;
            appendMatrixToFile(b1, n, 1, outputFile2);
            outputFile2 << endl;
            outputFile2 << "c1:" << endl;
            appendMatrixToFile(c1, n, 1, outputFile2);
            outputFile2 << endl;
            outputFile2 << "b1_plus_c1:" << endl;
            appendMatrixToFile(b1_plus_c1, n, 1, outputFile2);
            outputFile2 << endl;
            outputFile2 << "y2:" << endl;
            appendMatrixToFile(y2, n, 1, outputFile2);
            outputFile2 << endl;
            outputFile2 << "Y3y2_plus_y2_T:" << endl;
            appendMatrixToFile(Y3y2_plus_y2_T, 1, n, outputFile2);
            outputFile2 << endl;
            outputFile2.close();
        }
        else if (choice == 2) {
            int signal;
            MPI_Recv(&signal, 1, MPI_INT, 0, 901, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            cout << "<=== PROCESSOR 2 ===>" << endl << endl
                << "A1:" << endl << matrixToString(A1, n, n) << endl
                << "b1:" << endl << matrixToString(b1, n, 1) << endl
                << "c1:" << endl << matrixToString(c1, n, 1) << endl
                << "b1_plus_c1:" << endl << matrixToString(b1_plus_c1, n, 1) << endl
                << "y2:" << endl << matrixToString(y2, n, 1) << endl
                << "Y3y2_plus_y2_T:" << endl << matrixToString(Y3y2_plus_y2_T, 1, n) << endl;

            MPI_Send(&signal, 1, MPI_INT, 2, 902, MPI_COMM_WORLD);
        }

        

        // очищення памяті
        deleteMatrix(A1, n);
        deleteMatrix(b1, n);
        deleteMatrix(c1, n);
        deleteMatrix(b1_plus_c1, n);
        deleteMatrix(y2, n);

        deleteMatrix(Y3y2, n);
        deleteMatrix(Y3y2_plus_y2_T, 1);
        
        delete[] A1_recv;
        delete[] b1_recv;
        delete[] c1_recv;

        delete[] y2_send1;
        delete[] y2_send2;
        delete[] Y3y2_recv;
        delete[] Y3y2_plus_y2_T_send;
    }
    else if (rank == 2) {
        // отримання вибору і розміру
        int n, choice;
        MPI_Recv(&n, 1, MPI_INT, 1, 12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&choice, 1, MPI_INT, 1, 13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // отримання робочих матриць
        double* A2_recv = allocateMemoryFor1DArray(n * n);
        double* B2_recv = allocateMemoryFor1DArray(n * n);

        MPI_Recv(A2_recv, n * n, MPI_DOUBLE, 0, 207, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(B2_recv, n * n, MPI_DOUBLE, 0, 208, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        double** A2 = convertTo2D(A2_recv, n, n);
        double** B2 = convertTo2D(B2_recv, n, n);



        // створення і заповнення C2 ПО ЗАМОВЧУВАННЮ
        double** C2 = createEmptyMatrix(n, n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < n; j++) {
                C2[i - 1][j - 1] = 16 / (((double)i + (double)j) * ((double)i + (double)j));
            }
            C2[i - 1][n - 1] = 16 / (((double)i + (double)n) * ((double)i + (double)n));
        }



        // обрахунок Y3 = A2 * (B2 + 16 * C2)
        multiplyMatrixByScalar(C2, n, n, 16);
        double** B2_plus_C2 = addMatrices(B2, C2, n, n);
        double** Y3 = multiplyMatrices(A2, B2_plus_C2, n, n, n, n);

        double* Y3_send = convertTo1D(Y3, n, n);
        MPI_Send(Y3_send, n * n, MPI_DOUBLE, 0, 302, MPI_COMM_WORLD);



        // обрахунки x
        double* y2_recv = allocateMemoryFor1DArray(n * 1);
        MPI_Recv(y2_recv, n * 1, MPI_DOUBLE, 1, 315, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        double** y2 = convertTo2D(y2_recv, n, 1);
        double** Y3y2 = multiplyMatrices(Y3, y2, n, n, n, 1);

        double* Y3y2_send = convertTo1D(Y3y2, n, 1);
        MPI_Send(Y3y2_send, n * 1, MPI_DOUBLE, 1, 310, MPI_COMM_WORLD);

        double** Y3Y3y2 = multiplyMatrices(Y3y2, y2, n, n, n, 1);

        double* Y3Y3y2_send = convertTo1D(Y3Y3y2, n, 1);
        MPI_Send(Y3Y3y2_send, n * 1, MPI_DOUBLE, 0, 303, MPI_COMM_WORLD);



        // типи виводу
        if (choice == 1) {
            // створення і заповнення файлу
            ofstream outputFile3("Processor3.txt", ios::app);
            outputFile3 << "<=== PROCESSOR 3 ===>" << endl << endl;
            outputFile3 << "A2:" << endl;
            appendMatrixToFile(A2, n, n, outputFile3);
            outputFile3 << endl;
            outputFile3 << "B2:" << endl;
            appendMatrixToFile(B2, n, n, outputFile3);
            outputFile3 << endl;
            outputFile3 << "C2:" << endl;
            appendMatrixToFile(C2, n, n, outputFile3);
            outputFile3 << endl;
            outputFile3 << "Y3:" << endl;
            appendMatrixToFile(Y3, n, n, outputFile3);
            outputFile3 << endl;
            outputFile3 << "Y3y2:" << endl;
            appendMatrixToFile(Y3y2, n, 1, outputFile3);
            outputFile3 << endl;
            outputFile3 << "Y3Y3y2:" << endl;
            appendMatrixToFile(Y3Y3y2, n, 1, outputFile3);
            outputFile3 << endl;
            outputFile3.close();            
        }
        else if (choice == 2) {
            int signal;
            MPI_Recv(&signal, 1, MPI_INT, 1, 902, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            cout << "<=== PROCESSOR 3 ===>" << endl << endl
                << "A2:" << endl << matrixToString(A2, n, n) << endl
                << "B2:" << endl << matrixToString(B2, n, n) << endl
                << "C2:" << endl << matrixToString(C2, n, n) << endl
                << "Y3:" << endl << matrixToString(Y3, n, n) << endl
                << "Y3y2:" << endl << matrixToString(Y3y2, n, 1) << endl
                << "Y3Y3y2:" << endl << matrixToString(Y3Y3y2, n, 1) << endl;
        }
        


        // очищення памяті
        deleteMatrix(A2, n);
        deleteMatrix(B2, n);
        deleteMatrix(C2, n);
        deleteMatrix(B2_plus_C2, n);
        deleteMatrix(Y3, n);

        deleteMatrix(y2, n);
        deleteMatrix(Y3y2, n);
        deleteMatrix(Y3Y3y2, n);

        delete[] A2_recv;
        delete[] B2_recv;
        delete[] y2_recv;
        delete[] Y3y2_send;
        delete[] Y3Y3y2_send;
    }
    MPI_Finalize();



    return 0;
}





// Функція для створення пустої матриці заданого розміру
double** createEmptyMatrix(int rows, int cols) {
    // Виділення пам'яті для двовимірного масиву
    double** matrix = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

// виділення пам'яті під одновимірний масив
double* allocateMemoryFor1DArray(int size) {
    return new double[size];
}

// Функція для звільнення пам'яті, зайнятої матрицею
void deleteMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Функція для заповнення матриці з клавіатури
void fillMatrix(double** matrix, int rows, int cols) {
    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "Enter element at position [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }
}

// Функція для заповнення матриці випадковими числами
void fillMatrixRandom(double** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = (double)(rand() % 10 + 1);
        }
    }
}

// Функція для вибору заповнення
void chooseTypeFill(double** matrix, int rows, int cols) {
    int choice;
    while (true) {
        cout << "Enter 1 to manually or 2 to generation: ";
        cin >> choice;
        if (choice == 1) {
            fillMatrix(matrix, rows, cols);
            cout << "Matrix is full." << endl << endl;
            break;
        }
        else if (choice == 2) {
            fillMatrixRandom(matrix, rows, cols);
            cout << "Matrix is full." << endl << endl;
            break;
        }
        else {
            cout << "Wrong option. Try again." << endl << endl;
        }
    }
}

// Функція для множення двох матриць
double** multiplyMatrices(double** matrix1, double** matrix2, int rows1, int cols1, int rows2, int cols2) {
    if (cols1 != rows2) {
        cout << "Error: Number of columns in the first matrix must be equal to the number of rows in the second matrix." << endl;
        return nullptr;
    }
    double** resultMatrix = createEmptyMatrix(rows1, cols2);
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

// Функція для множення матриці на число
void multiplyMatrixByScalar(double** matrix, int rows, int cols, int scalar) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] *= scalar;
        }
    }
}

// Функція для додавання двох матриць
double** addMatrices(double** matrix1, double** matrix2, int rows, int cols) {
    double** resultMatrix = createEmptyMatrix(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            resultMatrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return resultMatrix;
}

// Функція для транспонування матриці
double** transposeMatrix(double** matrix, int rows, int cols) {
    double** transposedMatrix = createEmptyMatrix(cols, rows);
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            transposedMatrix[i][j] = matrix[j][i];
        }
    }
    return transposedMatrix;
}

// Функція для визначення визначника матриці
double determinant(double** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    double det = 0;
    double** submatrix = createEmptyMatrix(n - 1, n - 1);
    double sign = 1;
    for (int i = 0; i < n; ++i) {
        int subi = 0;
        for (int j = 1; j < n; ++j) {
            int subj = 0;
            for (int k = 0; k < n; ++k) {
                if (k == i) continue;
                submatrix[subi][subj] = matrix[j][k];
                ++subj;
            }
            ++subi;
        }
        det += sign * matrix[0][i] * determinant(submatrix, n - 1);
        sign = -sign;
    }
    deleteMatrix(submatrix, n - 1);
    return det;
}

// Функція для виводу матриці на екран
void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функція для створення стрінги з матриці
string matrixToString(double** matrix, int rows, int cols) {
    string result;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result += to_string(matrix[i][j]) + " ";
        }
        result += "\n"; // Додаємо роздільник нового рядка після кожного рядка матриці
    }
    return result;
}

// Функція для запису матриці у файл (дозапис)
void appendMatrixToFile(double** matrix, int rows, int cols, ofstream &outputFile) {
    if (!outputFile.is_open()) {
        cout << "Error: Unable to open file for writing." << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << endl;
    }
}

// Функція для конвертації двовимірного масиву у одновимірний
double* convertTo1D(double** array, int rows, int cols) {
    double* result = new double[rows * cols];
    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[index++] = array[i][j];
        }
    }
    return result;
}

// Функція для конвертації одновимірного масиву у двовимірний
double** convertTo2D(double* array, int rows, int cols) {
    double** result = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        result[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            result[i][j] = array[i * cols + j];
        }
    }
    return result;
}