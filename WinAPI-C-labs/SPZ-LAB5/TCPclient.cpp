// TCP клієнт
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("TCP Клієнт \n");
	printf("___________\n\n");
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in ServerAddr, ca;
	u_short Port = 5150;
	int Ret;
	char DataBuffer[1024];
	int caSize = sizeof(ca);

	// Ініціалізація Winsock версії 2.2
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		//Winsock не завантажився. Код помилки повертає функция WSAStartup
		printf("Помилка WSAStartup, номер помилки %d\n", Ret);
		return 1;
	}

	// Створимо новий сокет для з'єднання цього TCP клієнта
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		printf("Помилка socket, номер помилки %d\n", WSAGetLastError());
		WSACleanup();
		return 2;
	}

	// Заповнимо у змінній ServerAddr адресну інформацію про сервер, до якого ми хочемо підключитися.
	// Сервер слухає порт 5150, IP-адресу сервера вводимо з клавіатури
	char ipAddress[32];
	printf("Введіть IP - адресу сервера : ");
	gets_s(ipAddress);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = inet_addr(ipAddress);

	// З'єднаємо сокет s з сервером
	printf("Спроба з'єднання з %s : %d ...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
	if (connect(s, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("Помилка connect, номер помилки %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 3;
	}
	printf("З'єднання успішне.\n");

	// Отримуємо інформацію про адресу та порт клієнта
	getsockname(s, (struct sockaddr*)&ca, &caSize);
	printf("Адреса і порт клінта %s : %d \n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));

	// Тепер ми можемо обмінюватися даними з сервером через сокет s
	int num;
	char str[4];
	printf("Введіть розмір матриці: ");
	scanf_s("%d", &num);
	sprintf_s(str, "%d", num);
	const char* message = str;
	printf("Спроба передати повідомлення.\n");
	if ((Ret = send(s, message, sizeof(message), 0)) == SOCKET_ERROR) {
		printf("Помилка send, номер помилки %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 4;
	}
	printf("Успішно передано %d байт повідомлення \"%s\".\n", Ret, message);

	// Отримуємо дані від сервера
	printf("Чекаємо дані для отримання...\n");
	if ((Ret = recv(s, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("Помилка recv, номер помилки %d\n", WSAGetLastError());
		closesocket(s);
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
	printf("Успішно отримано %d байт в повідомленні \"%s\".\n", Ret, DataBuffer);
	printf("Закриваємо з'єднання з сервером.\n");
	closesocket(s);

	// Вивантажуємо Winsock
	WSACleanup();
	printf("Натисніть Enter для завершення.\n");
	getchar();
	getchar();

	return 0;
}