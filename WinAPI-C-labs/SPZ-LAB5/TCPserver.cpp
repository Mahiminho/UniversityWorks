// TCP сервер
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("TCP Сервер \n");
	printf("___________\n\n");
	WSADATA wsaData;
	SOCKET ListeningSocket;
	SOCKET NewConnection;
	struct sockaddr_in ServerAddr;
	struct sockaddr_in ClientAddr;
	int ClientAddrLen;
	u_short Port = 5150;
	int Ret;
	char DataBuffer[1024];

	// Ініціалізація Winsock версії 2.2
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		//Winsock не завантажився. Код помилки повертає функция WSAStartup
		printf("Помилка WSAStartup, номер помилки %d\n", Ret);
		return -1;
	}

	// Створимо новий TCP сокет для для прийому запитів на з'єднання від клієнтів.
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("Помилка socket, номер помилки %d\n", WSAGetLastError());
		WSACleanup();
		return -2;
	}

	// Заповнюємо struct sockaddr_in ServerAddr, яка скаже функції
	// bind, що ми хочемо слухати з'єднання на всіх інтерфейсах
	// (INADDR_ANY), використовуючи порт 5150.

	// Ми перетворюємо порядок байтів з системного у мережний (htons та htonl)
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Функція bind прив'язує адресну інформацію, визначену в ServerAddr до сокету ListeningSocket
	if (bind(ListeningSocket, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("Помилка bind, номер помилки %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -3;
	}

	// Робимо сокет пасивним для прослуховування (прийому) запитів на TCP-з'єднання від клієнтів.Довжина черги запитів на з'єднання дорівнює 5
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		printf("Помилка listen, номер помилки %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -4;
	}
	printf("Чекаємо з'єднання на порту %d.\n", Port);

	ClientAddrLen = sizeof(ClientAddr);

	// Приймаємо нове з'єднання, коли воно виникне
	if ((NewConnection = accept(ListeningSocket, (struct sockaddr*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET) {
		printf("Помилка accept, номер помилки %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -5;
	}
	printf("Успішно з'єдналися з %s:%d.\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

	// Далі ми можемо знову очікувати на сокеті ListeningSocket
	// нові з'єднання знову, викликаючи accept та/або почати
	// передавати та приймати дані на сокеті NewConnection.

	// Для простоти зупинимо прослуховування, закриваючи сокет
	// ListeningSocket. Можна починати прийом та передачу даних на
	// сокеті NewConnection.

	closesocket(ListeningSocket);
	printf("Чекаємо дані для отримання...\n");
	if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("Помилка recv, номер помилки %d\n", WSAGetLastError());
		closesocket(NewConnection);
		WSACleanup();
		return -6;
	}

	// Створюємо з отриманих даних рядок мови С
	if (Ret <= 1023) {
		DataBuffer[Ret] = '\0';
	}
	else {
		printf("Повідомлення задовге!\n");
		return -7;
	}
	DataBuffer[Ret] = '\0';
	printf("Успішно отримано %d байтів в повідомленні \"%s\".\n", Ret, DataBuffer);

	// Отримання числа з повідомлення
	int n = atoi(DataBuffer);
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
	printf("Original array:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", dynamicArray[i][j]);
		}
		printf("\n");
	}

	// Знаходження найменшого числа в матриці
	int min_num = dynamicArray[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dynamicArray[i][j] < min_num)
				min_num = dynamicArray[i][j];
		}
	}

	// Перетворення числа в повідомлення
	char str[4];
	sprintf_s(str, "%d", min_num);
	const char* message = str;

	//Передаємо повідомлення клієнту
	printf("Спроба передати повідомлення клієнту...\n");
	if ((Ret = send(NewConnection, message, strlen(message), 0)) == SOCKET_ERROR) {
		printf("Помилка send, номер помилки %d\n", WSAGetLastError());
		closesocket(NewConnection);
		WSACleanup();
		return -8;
	}
	printf("Успішно передано %d байт повідомлення \"%s\".\n", Ret, message);
	printf("Закриваємо з'єднання з клієнтом.\n");
	closesocket(NewConnection);

	// Вивантажуємо Winsock
	WSACleanup();
	printf("Натисніть Enter для завершення.\n");
	getchar();
	getchar();

	return 0;
}