#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Програма демонструє управління структурою даних типу «черга», елементами якого є значення типу double.
// Черга реалізована за допомогою динамічного масиву розміром 20 Кб

// Операції, що виконуються над чергою: 
// •перевірити, черга порожня чи не порожня; 
// •додати елемент в хвіст черги; 
// •видалити елемент з голови черги;
// •переглянути голову черги;
// •вивести на екран елементи черги, починаючи з першого.

#define QUEUE_CAPACITY_Byte 20480
#define QUEUE_CAPACITY (QUEUE_CAPACITY_Byte / sizeof(double))

// елемент черги
typedef struct QueueNode {
	double* data;
	struct QueueNode* next;
} QueueNode;

// черга
typedef struct {
	QueueNode* front;
	QueueNode* rear;
	size_t size; // фактичний розмір
    size_t capacity; // максимальний розмір
} Queue;

// створення черги
void createQueue(Queue** queue) {
    *queue = (Queue*)VirtualAlloc(NULL, QUEUE_CAPACITY_Byte, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!(*queue)) {
        perror("Failed to allocate memory for the queue!\n");
        exit(EXIT_FAILURE);
    }
    (*queue)->front = NULL;
    (*queue)->rear = NULL;
    (*queue)->size = 0;
    (*queue)->capacity = QUEUE_CAPACITY;
}

// видалення черги
void destroyQueue(Queue* queue) {
    VirtualFree(queue, 0, MEM_RELEASE);
}

// перевірка чи черга порожня
int isEmpty(Queue* queue) {
    return queue->size == 0;
}

// додавання елемента в хвіст черги
void pushBack(Queue* queue, double value) {
    if (queue->size >= queue->capacity) {
        perror("Queue is full!\n");
        exit(EXIT_FAILURE);
    }
    QueueNode* newNode = (QueueNode*)VirtualAlloc(NULL, sizeof(QueueNode), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!newNode) {
        perror("Failed to allocate memory for the new node!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = (double*)VirtualAlloc(NULL, sizeof(double), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!(newNode->data)) {
        perror("Failed to allocate memory for the data!\n");
        exit(EXIT_FAILURE);
    }
    *(newNode->data) = value;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// видалення елемента з голови черги
void popFront(Queue* queue) {
    if (isEmpty(queue)) {
        perror("Queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    VirtualFree(temp->data, 0, MEM_RELEASE);
    VirtualFree(temp, 0, MEM_RELEASE);
    queue->size--;
}

// перегляд елемента в голові черги
double getFront(Queue* queue) {
    if (isEmpty(queue)) {
        perror("Queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    return *(queue->front->data);
}

// вивід елементів черги, починаючи з першого
void printQueue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    QueueNode* current = queue->front;
    printf("Queue elements (from front to rear):\n");
    while (current != NULL) {
        printf("%lf ", *(current->data));
        current = current->next;
    }
    printf("\n\n");
}



int main() {
    Queue* myQueue;
    createQueue(&myQueue);
    printf("Queue created.\n\n");

    printf("Is queue empty? %s\n\n", isEmpty(myQueue) ? "Yes." : "No.");

    pushBack(myQueue, 11.11);
    pushBack(myQueue, 22.222);
    pushBack(myQueue, 3.3);
    pushBack(myQueue, 4.444);
    pushBack(myQueue, 5.55);
    printf("Added 5 elements.\n\n");
    printQueue(myQueue);

    printf("Is queue empty? %s\n\n", isEmpty(myQueue) ? "Yes." : "No.");

    popFront(myQueue);
    printf("First element deleted.\n\n");
    printQueue(myQueue);

    printf("First element of queue: %lf.\n\n", getFront(myQueue));

    destroyQueue(myQueue);
    printf("Queue destroyed.\n");

    return 0;
}