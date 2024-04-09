#include <iostream>
#include <chrono>
#include "mpi.h"

using namespace std;

const int circle[] = { 6, 2, 7, 1, 0, 3, 5, 4 };
const int procNumber = 8;
const int N1 = 217;
const int N2 = 149;
const int N3 = 95;
int procRank;

struct A {
	int row;
	int n1;
	int n2;
	double arr[N1 / 8 + N1][N2];
};

struct B {
	int col;
	int n2;
	int n3;
	double arr[N2][N3 / 8 + N3];
};

struct R {
	int n1;
	int n3;
	double arr[N1 / 8 + N1][N3];
};

int matrixA[N1][N2] = { 0 };
int matrixB[N2][N3] = { 0 };
A subA[procNumber];
B subB[procNumber];
R result[procNumber];
int procSize;

// send and multiply submatrices
void MultiplySubmatrices(A sub_A, B sub_B, int proc) {
	for (int i = 0; i < sub_A.n1; i++)
		for (int k = 0; k < sub_A.n2; k++)
			for (int j = 0; j < sub_B.n3; j++)
				result[proc].arr[i][j + sub_B.col] += sub_A.arr[i][k] * sub_B.arr[k][j];
	result[proc].n1 = sub_A.n1;
	result[proc].n3 = N3;
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &procRank);
	MPI_Comm_size(MPI_COMM_WORLD, &procSize);
	MPI_Status Status;
	if (procSize != 8) {
		cout << "Must be 8 process!" << endl;
		MPI_Finalize();
		return 1;
	}

	// fill A
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			matrixA[i][j] = 1; // rand() % 99 + 10;
		}
	}

	// fill B
	for (int i = 0; i < N2; i++) {
		for (int j = 0; j < N3; j++) {
			matrixB[i][j] = 1; // rand() % 99 + 10;
		}
	}

	// break on submatrices A
	int rowsRest = N1;
	int rowsSum = 0;
	int restProc = procNumber;
	for (int i = 0; i < procNumber; i++) {
		if ((rowsRest % (restProc)) == 0) {
			subA[i].row = rowsSum;
			subA[i].n1 = rowsRest / restProc;
			subA[i].n2 = N2;
			rowsRest -= rowsRest / restProc;
		}
		else {
			subA[i].row = rowsSum;
			subA[i].n1 = rowsRest / restProc;
			subA[i].n2 = N2;
			rowsRest -= subA[i].n1;
		}

		for (int k = 0; k < subA[i].n1; k++) {
			for (int j = 0; j < subA[i].n2; j++) {
				subA[i].arr[k][j] = matrixA[k + rowsSum][j];
			}
		}
		rowsSum += subA[i].n1;
		restProc--;
	}

	// break on submatrices B
	rowsSum = 0;
	restProc = procNumber;
	rowsRest = N3;
	for (int i = 0; i < procNumber; i++) {
		if ((rowsRest % (restProc)) == 0) {
			subB[i].col = rowsSum;
			subB[i].n3 = rowsRest / restProc;
			subB[i].n2 = N2;
			rowsRest -= rowsRest / restProc;
		}
		else {
			subB[i].col = rowsSum;
			subB[i].n3 = rowsRest / restProc;
			subB[i].n2 = N2;
			rowsRest -= rowsRest / restProc;
		}
		for (int k = 0; k < subB[i].n2; k++) {
			for (int j = 0; j < subB[i].n3; j++) {
				subB[i].arr[k][j] = matrixB[k][j + rowsSum];
			}
		}
		rowsSum += subB[i].n3;
		restProc--;
	}

	if (procRank == 0) {
		auto start0 = chrono::high_resolution_clock::now();

		MPI_Send(&subA[1], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(A1)->S1" << endl;
		MPI_Send(&subA[2], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S0->(A2)->S2" << endl;
		MPI_Send(&subA[3], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S0->(A3)->S3" << endl;
		MPI_Send(&subA[4], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S0->(A4)->S4" << endl;
		MPI_Send(&subA[5], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S0->(A5)->S5" << endl;
		MPI_Send(&subA[6], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S0->(A6)->S6" << endl;
		MPI_Send(&subA[7], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S0->(A7)->S7" << endl;

		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B1)->S1" << endl;
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S0->(B2)->S2" << endl;
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S0->(B3)->S3" << endl;
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S0->(B4)->S4" << endl;
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S0->(B5)->S5" << endl;
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S0->(B6)->S6" << endl;
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S0->(B7)->S7" << endl;

		// A0 * B0
		MultiplySubmatrices(subA[0], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B0)->S1" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B5
		MultiplySubmatrices(subA[0], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B5)->S1" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B3
		MultiplySubmatrices(subA[0], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B3)->S1" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B7
		MultiplySubmatrices(subA[0], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B7)->S1" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B6
		MultiplySubmatrices(subA[0], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B6)->S1" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B4
		MultiplySubmatrices(subA[0], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B4)->S1" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B2
		MultiplySubmatrices(subA[0], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B2)->S1" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		// A0 * B1
		MultiplySubmatrices(subA[0], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
		cout << "S0->(B1)->S1" << endl;

		MPI_Recv(&result[1], sizeof(R), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[2], sizeof(R), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[3], sizeof(R), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[4], sizeof(R), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[5], sizeof(R), MPI_BYTE, 5, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[6], sizeof(R), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&result[7], sizeof(R), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);

		auto end0 = chrono::high_resolution_clock::now();
		auto duration0 = chrono::duration_cast<std::chrono::milliseconds>(end0 - start0);
		int time0 = duration0.count();

		int time1, time2, time3, time4, time5, time6, time7;
		MPI_Recv(&time1, 1, MPI_INT, 1, 101, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time2, 1, MPI_INT, 2, 102, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time3, 1, MPI_INT, 3, 103, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time4, 1, MPI_INT, 4, 104, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time5, 1, MPI_INT, 5, 105, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time6, 1, MPI_INT, 6, 106, MPI_COMM_WORLD, &Status);
		MPI_Recv(&time7, 1, MPI_INT, 7, 107, MPI_COMM_WORLD, &Status);

		int times[] = { time0, time1, time2, time3, time4, time5, time6, time7 };
		int max_time = times[0];
		for (int i = 1; i < 7; i++) {
			if (times[i] > max_time) {
				max_time = times[i];
			}
		}

		cout << endl << endl << "RESULT:" << endl;
		for (int k = 0; k < 8; k++) {
			cout << "Block: " << k + 1 << endl;
			for (int i = 0; i < result[k].n1; i++) {
				for (int j = 0; j < result[k].n3; j++) {
					cout << result[k].arr[i][j] << " ";
				}
				cout << endl << endl;
			}
		}

		cout << "\nTIME0: " << time0 << " ms." << endl;
		cout << "TIME1: " << time1 << " ms." << endl;
		cout << "TIME2: " << time2 << " ms." << endl;
		cout << "TIME3: " << time3 << " ms." << endl;
		cout << "TIME4: " << time4 << " ms." << endl;
		cout << "TIME5: " << time5 << " ms." << endl;
		cout << "TIME6: " << time6 << " ms." << endl;
		cout << "TIME7: " << time7 << " ms." << endl << endl;
		cout << "REAL TIME: " << max_time << " ms." << endl;
	}

	if (procRank == 1) {
		auto start1 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[1], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A1 * B1
		MultiplySubmatrices(subA[1], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B1)->S2" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B0
		MultiplySubmatrices(subA[1], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B0)->S2" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B5
		MultiplySubmatrices(subA[1], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B5)->S2" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B3
		MultiplySubmatrices(subA[1], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B3)->S2" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B7
		MultiplySubmatrices(subA[1], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B7)->S2" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B6
		MultiplySubmatrices(subA[1], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B6)->S2" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B4
		MultiplySubmatrices(subA[1], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B4)->S2" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		// A1 * B2
		MultiplySubmatrices(subA[1], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD);
		cout << "S1->(B2)->S2" << endl;
		MPI_Send(&result[1], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S1->(R1)->S0" << endl;

		auto end1 = chrono::high_resolution_clock::now();
		auto duration1 = chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
		int time1 = duration1.count();
		MPI_Send(&time1, 1, MPI_INT, 0, 101, MPI_COMM_WORLD);
	}

	if (procRank == 2) {
		auto start2 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[2], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A2 * B2
		MultiplySubmatrices(subA[2], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B2)->S4" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B1
		MultiplySubmatrices(subA[2], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B1)->S4" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B0
		MultiplySubmatrices(subA[2], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B0)->S4" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B5
		MultiplySubmatrices(subA[2], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B5)->S4" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B3
		MultiplySubmatrices(subA[2], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B3)->S4" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B7
		MultiplySubmatrices(subA[2], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B7)->S4" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B6
		MultiplySubmatrices(subA[2], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B6)->S4" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 1, 0, MPI_COMM_WORLD, &Status);
		// A2 * B4
		MultiplySubmatrices(subA[2], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD);
		cout << "S2->(B4)->S4" << endl;
		MPI_Send(&result[2], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S2->(R2)->S0" << endl;

		auto end2 = chrono::high_resolution_clock::now();
		auto duration2 = chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
		int time2 = duration2.count();
		MPI_Send(&time2, 1, MPI_INT, 0, 102, MPI_COMM_WORLD);
	}

	if (procRank == 3) {
		auto start3 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[3], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A3 * B3
		MultiplySubmatrices(subA[3], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B3)->S5" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B7
		MultiplySubmatrices(subA[3], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B7)->S5" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B6
		MultiplySubmatrices(subA[3], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B6)->S5" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B4
		MultiplySubmatrices(subA[3], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B4)->S5" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B2
		MultiplySubmatrices(subA[3], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B2)->S5" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B1
		MultiplySubmatrices(subA[3], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B1)->S5" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B0
		MultiplySubmatrices(subA[3], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B0)->S5" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD, &Status);
		// A3 * B5
		MultiplySubmatrices(subA[3], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 5, 0, MPI_COMM_WORLD);
		cout << "S3->(B5)->S5" << endl;
		MPI_Send(&result[3], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S3->(R3)->S0" << endl;

		auto end3 = chrono::high_resolution_clock::now();
		auto duration3 = chrono::duration_cast<std::chrono::milliseconds>(end3 - start3);
		int time3 = duration3.count();
		MPI_Send(&time3, 1, MPI_INT, 0, 103, MPI_COMM_WORLD);
	}

	if (procRank == 4) {
		auto start4 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[4], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A4 * B4
		MultiplySubmatrices(subA[4], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B4)->S6" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B2
		MultiplySubmatrices(subA[4], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B2)->S6" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B1
		MultiplySubmatrices(subA[4], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B1)->S6" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B0
		MultiplySubmatrices(subA[4], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B0)->S6" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B5
		MultiplySubmatrices(subA[4], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B5)->S6" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B3
		MultiplySubmatrices(subA[4], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B3)->S6" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B7
		MultiplySubmatrices(subA[4], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B7)->S6" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 2, 0, MPI_COMM_WORLD, &Status);
		// A4 * B6
		MultiplySubmatrices(subA[4], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD);
		cout << "S4->(B6)->S6" << endl;
		MPI_Send(&result[4], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S4->(R4)->S0" << endl;

		auto end4 = chrono::high_resolution_clock::now();
		auto duration4 = chrono::duration_cast<std::chrono::milliseconds>(end4 - start4);
		int time4 = duration4.count();
		MPI_Send(&time4, 1, MPI_INT, 0, 104, MPI_COMM_WORLD);
	}

	if (procRank == 5) {
		auto start5 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[5], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A5 * B5
		MultiplySubmatrices(subA[5], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B5)->S0" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B3
		MultiplySubmatrices(subA[5], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B3)->S0" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B7
		MultiplySubmatrices(subA[5], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B7)->S0" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B6
		MultiplySubmatrices(subA[5], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B6)->S0" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B4
		MultiplySubmatrices(subA[5], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B4)->S0" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B2
		MultiplySubmatrices(subA[5], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B2)->S0" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B1
		MultiplySubmatrices(subA[5], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(B1)->S0" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD, &Status);
		// A5 * B0
		MultiplySubmatrices(subA[5], subB[0], procRank);

		MPI_Send(&result[5], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S5->(R5)->S0" << endl;

		auto end5 = chrono::high_resolution_clock::now();
		auto duration5 = chrono::duration_cast<std::chrono::milliseconds>(end5 - start5);
		int time5 = duration5.count();
		MPI_Send(&time5, 1, MPI_INT, 0, 105, MPI_COMM_WORLD);
	}

	if (procRank == 6) {
		auto start6 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[6], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A6 * B6
		MultiplySubmatrices(subA[6], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B6)->S7" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B4
		MultiplySubmatrices(subA[6], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B4)->S7" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B2
		MultiplySubmatrices(subA[6], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B2)->S7" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B1
		MultiplySubmatrices(subA[6], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B1)->S7" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B0
		MultiplySubmatrices(subA[6], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B0)->S7" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B5
		MultiplySubmatrices(subA[6], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B5)->S7" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B3
		MultiplySubmatrices(subA[6], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B3)->S7" << endl;

		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 4, 0, MPI_COMM_WORLD, &Status);
		// A6 * B7
		MultiplySubmatrices(subA[6], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 7, 0, MPI_COMM_WORLD);
		cout << "S6->(B7)->S7" << endl;
		MPI_Send(&result[6], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S6->(R6)->S0" << endl;

		auto end6 = chrono::high_resolution_clock::now();
		auto duration6 = chrono::duration_cast<std::chrono::milliseconds>(end6 - start6);
		int time6 = duration6.count();
		MPI_Send(&time6, 1, MPI_INT, 0, 106, MPI_COMM_WORLD);
	}

	if (procRank == 7) {
		auto start7 = chrono::high_resolution_clock::now();

		MPI_Recv(&subA[7], sizeof(A), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);
		MPI_Recv(&subB[7], sizeof(B), MPI_BYTE, 0, 0, MPI_COMM_WORLD, &Status);

		// A7 * B7
		MultiplySubmatrices(subA[7], subB[7], procRank);
		MPI_Send(&subB[7], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B7)->S3" << endl;

		MPI_Recv(&subB[6], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B6
		MultiplySubmatrices(subA[7], subB[6], procRank);
		MPI_Send(&subB[6], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B6)->S3" << endl;

		MPI_Recv(&subB[4], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B4
		MultiplySubmatrices(subA[7], subB[4], procRank);
		MPI_Send(&subB[4], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B4)->S3" << endl;

		MPI_Recv(&subB[2], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B2
		MultiplySubmatrices(subA[7], subB[2], procRank);
		MPI_Send(&subB[2], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B2)->S3" << endl;

		MPI_Recv(&subB[1], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B1
		MultiplySubmatrices(subA[7], subB[1], procRank);
		MPI_Send(&subB[1], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B1)->S3" << endl;

		MPI_Recv(&subB[0], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B0
		MultiplySubmatrices(subA[7], subB[0], procRank);
		MPI_Send(&subB[0], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B0)->S3" << endl;

		MPI_Recv(&subB[5], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B5
		MultiplySubmatrices(subA[7], subB[5], procRank);
		MPI_Send(&subB[5], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B5)->S3" << endl;

		MPI_Recv(&subB[3], sizeof(B), MPI_BYTE, 6, 0, MPI_COMM_WORLD, &Status);
		// A7 * B3
		MultiplySubmatrices(subA[7], subB[3], procRank);
		MPI_Send(&subB[3], sizeof(B), MPI_BYTE, 3, 0, MPI_COMM_WORLD);
		cout << "S7->(B3)->S3" << endl;
		MPI_Send(&result[7], sizeof(R), MPI_BYTE, 0, 0, MPI_COMM_WORLD);
		cout << "S7->(R7)->S0" << endl;

		auto end7 = chrono::high_resolution_clock::now();
		auto duration7 = chrono::duration_cast<std::chrono::milliseconds>(end7 - start7);
		int time7 = duration7.count();
		MPI_Send(&time7, 1, MPI_INT, 0, 107, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}