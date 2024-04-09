
// Програма знаходить найменше число у динамічному двовимірному масиві
// Знаходження найменшого елементу масиву оформлено у вигляді функції потоку
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Структура для передачі аргументів у функцію потоку
struct ThreadArgs {
	int** array; // Динамічний масив
	int array_size; // Розмір масиву
};

// Функція потоку для обертання масиву
DWORD WINAPI reverseArray(LPVOID lpParam) {
	struct ThreadArgs* threadArgs = (struct ThreadArgs*)lpParam;
	int** array = threadArgs->array;
	int size = threadArgs->array_size;
	int min_num = array[0][0];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (array[i][j] < min_num)
				min_num = array[i][j];
		}
	}
	printf("Minimum number: %d", min_num);
	return 0;
}

int main() {
	int n;
	printf("Enter the size of the array: ");
	scanf_s("%d", &n);
	srand(time(NULL));

	// Генерування динамічного масиву з випадковими значеннями
	int** dynamicArray = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		dynamicArray[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dynamicArray[i][j] = rand() % 100; // Випадкові значення від 0 до 99
		}
	}

	// Виведення початкового масиву
	printf("\nOriginal array:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", dynamicArray[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// Створення структури з аргументами для функції потоку
	struct ThreadArgs threadArgs;
	threadArgs.array = dynamicArray;
	threadArgs.array_size = n;
	HANDLE hThread;
	DWORD dwThreadId;

	// Створення потоку для обертання масиву
	hThread = CreateThread(
		NULL, // default security attributes
		0, // use default stack size
		reverseArray, // thread function
		&threadArgs, // argument to thread function
		0, // use default creation flags
		&dwThreadId); // returns the thread identifier
	if (hThread == NULL) {
		fprintf(stderr, "Error creating thread (%lu).\n", GetLastError());
		return 1;
	}

	// Чекаємо завершення потоку
	WaitForSingleObject(hThread, INFINITE);

	// Виведення інформації про потік та основний процес
	printf("\nThread ID: %lu\n", dwThreadId);
	printf("Thread Handle: %p\n\n", hThread);
	printf("Main process ID: %lu\n", GetCurrentProcessId());
	printf("Main thread ID: %lu\n", GetCurrentThreadId());
	printf("Main process Handle: %p\n", GetCurrentProcess());
	printf("Main thread Handle: %p\n", GetCurrentThread());

	// Закриття дескрипторів, які більше не потрібні
	CloseHandle(hThread);
	for (int i = 0; i < n; i++) {
		free(dynamicArray[i]);
	}
	free(dynamicArray);
	getchar(); 
	getchar();
	return 0;
}
