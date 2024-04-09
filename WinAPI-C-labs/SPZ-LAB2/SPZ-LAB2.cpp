#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// Програма знаходить найменший елемент двовимірного динамічного масиву розміру n на n
// Знаходження найменшого елемента оформлено у вигляді функції потоку.
// Потік запускається на виконання декілька раз з різними рівнями пріоритету

// змінна, що зберігатиме найменше значення матриці для виведення
int globalMinNum;

// Структура для передачі аргументів у функцію потоку
struct ThreadArgs {
	int array_size; // Розмір масиву
};

// Функція потоку для знаходження найменшого елемента
DWORD WINAPI reverseArray(LPVOID lpParam) {
	srand(time(NULL));
	struct ThreadArgs* threadArgs = (struct ThreadArgs*)lpParam;
	int size = threadArgs->array_size;

	// Генерування динамічного масиву з випадковими значеннями
	int** dynamicArray = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		dynamicArray[i] = (int*)malloc(size * sizeof(int));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			dynamicArray[i][j] = rand() % 100; // Випадкові значення від 0 до 99
		}
	}

	// знаходження найменшого елемента
	int min_num = dynamicArray[0][0];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (dynamicArray[i][j] < min_num)
				min_num = dynamicArray[i][j];
		}
	}
	globalMinNum = min_num;

	// звільнення памяті
	for (int i = 0; i < size; i++) {
		free(dynamicArray[i]);
	}
	free(dynamicArray);

	return 0;
}

int main() {
	int n;
	printf("Enter the size of the matrix: ");
	scanf_s("%d", &n);

	// Отримання дескриптора поточного процесу
	HANDLE hProcess = GetCurrentProcess();

	// Отримання пріоритету класу для поточного процесу
	int priorityClass = GetPriorityClass(hProcess);
	printf("Priority class for the current process: %d\n", priorityClass);

	// Створення структури з аргументами для функції потоку
	struct ThreadArgs threadArgs;
	threadArgs.array_size = n;
	HANDLE hThread;
	DWORD dwThreadId;

	// Послідовно запускаємо потік з різними рівнями пріоритету
	for (int priority = THREAD_PRIORITY_IDLE; priority <= THREAD_PRIORITY_TIME_CRITICAL; priority += 10) {
		// Створення потоку з вказаним рівнем пріоритету
		hThread = CreateThread(
			NULL, // default security attributes
			0, // use default stack size
			reverseArray, // thread function
			&threadArgs, // argument to thread function
			CREATE_SUSPENDED, // create suspended initially
			&dwThreadId); // returns the thread identifier
		if (hThread == NULL) {
			fprintf(stderr, "Error creating thread (%lu).\n", GetLastError());
			return 1;
		}

		// Задання рівня пріоритету потоку
		SetThreadPriority(hThread, priority);

		// Пускаємо потік у виконання
		ResumeThread(hThread);

		// Чекаємо завершення потоку
		WaitForSingleObject(hThread, INFINITE);

		// Виведення найменшого елемента
		printf("---------------------------------------------------\n");
		printf("The smallest element of matrix with priority %d: %d\n", priority, globalMinNum);

		// Визначення часу виконання потоку за допомогою GetThreadTimes()
		FILETIME creationTime, exitTime, kernelTime, userTime;
		if (GetThreadTimes(hThread, &creationTime, &exitTime, &kernelTime, &userTime)) {
			ULARGE_INTEGER kernelTimeInt, userTimeInt;
			kernelTimeInt.LowPart = kernelTime.dwLowDateTime;
			kernelTimeInt.HighPart = kernelTime.dwHighDateTime;
			userTimeInt.LowPart = userTime.dwLowDateTime;
			userTimeInt.HighPart = userTime.dwHighDateTime;

			printf("\nKernel Time: %.20f milliseconds\n", kernelTimeInt.QuadPart * 1e-4);
			printf("User Time: %.20f milliseconds\n", userTimeInt.QuadPart * 1e-4);

			SYSTEMTIME systemTime;
			FileTimeToSystemTime(&creationTime, &systemTime); // Перетворення часу у формат SYSTEMTIME
			printf("\nThread start time: %u:%u:%u:%u\n", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);
			FileTimeToSystemTime(&exitTime, &systemTime); // Перетворення часу у формат SYSTEMTIME
			printf("Thread end time: %u:%u:%u:%u\n", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds);

			ULONGLONG ThreadCycleTime;
			QueryThreadCycleTime(hThread, &ThreadCycleTime);
			printf("\nThread execution time : %llu tacts\n", ThreadCycleTime);
		}

		// Закриття дескрипторів, які більше не потрібні
		CloseHandle(hThread);
	}

	return 0;
}