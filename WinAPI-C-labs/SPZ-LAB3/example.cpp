#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Програма демонструє управління структурою даних типу «динамічний вектор», елементами якого є значення типу int.
// Динамічний вектор реалізований за допомогою динамічного масиву розміром 1 Кб

// Операції, що виконуються над вектором: 
// •перевірити, вектор порожній чи не порожній; 
// •прочитати елемент із зазначеним індексом; 
// •змінити значення елемента з вказаним індексом; 
// •додати елемент в кінець вектору.

#define VECTOR_CAPACITY_Byte 1024
#define VECTOR_CAPACITY (VECTOR_CAPACITY_Byte / sizeof(int))

typedef struct
{
	int* data;
	size_t size;
	size_t capacity;
} DynamicVector;

void createDynamicVector(DynamicVector* vector)
{

	vector->data = (int*)VirtualAlloc(NULL, VECTOR_CAPACITY_Byte, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (vector->data == NULL)
	{
		perror("Error allocating memory for vector data");
		exit(EXIT_FAILURE);
	}
	vector->size = 0;
	vector->capacity = VECTOR_CAPACITY;
}

int isEmpty(DynamicVector* vector)
{
	return vector->size == 0;
}

int getElement(DynamicVector* vector, size_t index)
{
	if (index < vector->size)
		return vector->data[index];
	else
	{
		fprintf(stderr, "Index out of bounds\n");
		exit(EXIT_FAILURE);
	}
}

void setElement(DynamicVector* vector, size_t index, int value)
{
	if (index < vector->size)
		vector->data[index] = value;
	else
	{
		fprintf(stderr, "Index out of bounds\n");
		exit(EXIT_FAILURE);
	}
}

void addElement(DynamicVector* vector, int value)
{
	if (vector->size < vector->capacity)
	{
		vector->data[vector->size] = value;
		vector->size++;
	}
	else
	{
		fprintf(stderr, "Vector capacity exceeded\n");
		exit(EXIT_FAILURE);
	}
}

void destroyDynamicVector(DynamicVector* vector)
{
	if (vector->data != NULL)
		VirtualFree(vector->data, 0, MEM_RELEASE);
}

int main1()
{
	DynamicVector myVector;
	createDynamicVector(&myVector);
	printf("\nIs vector empty? %s\n", isEmpty(&myVector) ? "Yes" : "No");

	for (size_t i = 0; i < 5; ++i)
		addElement(&myVector, i * 2);

	printf("\nIs vector empty? %s\n", isEmpty(&myVector) ? "Yes" : "No");
	printf("\n");

	for (size_t i = 0; i < myVector.size; ++i)
		printf("Element at index %zu: %d\n", i, getElement(&myVector, i));
	printf("\n");

	size_t indexToModify = 2;
	int newValue = 42;
	setElement(&myVector, indexToModify, newValue);
	printf("Element at index %zu after modification: %d\n", indexToModify,
	getElement(&myVector, indexToModify));
	destroyDynamicVector(&myVector);
	return 0;
}