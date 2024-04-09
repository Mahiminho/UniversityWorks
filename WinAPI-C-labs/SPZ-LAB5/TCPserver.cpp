// TCP ������
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

int main(void) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("TCP ������ \n");
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

	// ����������� Winsock ���� 2.2
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		//Winsock �� ������������. ��� ������� ������� ������� WSAStartup
		printf("������� WSAStartup, ����� ������� %d\n", Ret);
		return -1;
	}

	// �������� ����� TCP ����� ��� ��� ������� ������ �� �'������� �� �볺���.
	if ((ListeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		printf("������� socket, ����� ������� %d\n", WSAGetLastError());
		WSACleanup();
		return -2;
	}

	// ���������� struct sockaddr_in ServerAddr, ��� ����� �������
	// bind, �� �� ������ ������� �'������� �� ��� �����������
	// (INADDR_ANY), �������������� ���� 5150.

	// �� ������������ ������� ����� � ���������� � �������� (htons �� htonl)
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// ������� bind ����'��� ������� ����������, ��������� � ServerAddr �� ������ ListeningSocket
	if (bind(ListeningSocket, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("������� bind, ����� ������� %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -3;
	}

	// ������ ����� �������� ��� ��������������� (�������) ������ �� TCP-�'������� �� �볺���.������� ����� ������ �� �'������� ������� 5
	if (listen(ListeningSocket, 5) == SOCKET_ERROR) {
		printf("������� listen, ����� ������� %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -4;
	}
	printf("������ �'������� �� ����� %d.\n", Port);

	ClientAddrLen = sizeof(ClientAddr);

	// �������� ���� �'�������, ���� ���� �������
	if ((NewConnection = accept(ListeningSocket, (struct sockaddr*)&ClientAddr, &ClientAddrLen)) == INVALID_SOCKET) {
		printf("������� accept, ����� ������� %d\n", WSAGetLastError());
		closesocket(ListeningSocket);
		WSACleanup();
		return -5;
	}
	printf("������ �'�������� � %s:%d.\n", inet_ntoa(ClientAddr.sin_addr), ntohs(ClientAddr.sin_port));

	// ��� �� ������ ����� ��������� �� ����� ListeningSocket
	// ��� �'������� �����, ���������� accept ��/��� ������
	// ���������� �� �������� ��� �� ����� NewConnection.

	// ��� �������� �������� ���������������, ���������� �����
	// ListeningSocket. ����� �������� ������ �� �������� ����� ��
	// ����� NewConnection.

	closesocket(ListeningSocket);
	printf("������ ��� ��� ���������...\n");
	if ((Ret = recv(NewConnection, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("������� recv, ����� ������� %d\n", WSAGetLastError());
		closesocket(NewConnection);
		WSACleanup();
		return -6;
	}

	// ��������� � ��������� ����� ����� ���� �
	if (Ret <= 1023) {
		DataBuffer[Ret] = '\0';
	}
	else {
		printf("����������� �������!\n");
		return -7;
	}
	DataBuffer[Ret] = '\0';
	printf("������ �������� %d ����� � ���������� \"%s\".\n", Ret, DataBuffer);

	// ��������� ����� � �����������
	int n = atoi(DataBuffer);
	srand(time(NULL));

	// ����������� ���������� ������ � ����������� ����������
	int** dynamicArray = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		dynamicArray[i] = (int*)malloc(n * sizeof(int));
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dynamicArray[i][j] = rand() % 100; // �������� �������� �� 0 �� 99
		}
	}

	// ��������� ����������� ������
	printf("Original array:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", dynamicArray[i][j]);
		}
		printf("\n");
	}

	// ����������� ���������� ����� � �������
	int min_num = dynamicArray[0][0];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (dynamicArray[i][j] < min_num)
				min_num = dynamicArray[i][j];
		}
	}

	// ������������ ����� � �����������
	char str[4];
	sprintf_s(str, "%d", min_num);
	const char* message = str;

	//�������� ����������� �볺���
	printf("������ �������� ����������� �볺���...\n");
	if ((Ret = send(NewConnection, message, strlen(message), 0)) == SOCKET_ERROR) {
		printf("������� send, ����� ������� %d\n", WSAGetLastError());
		closesocket(NewConnection);
		WSACleanup();
		return -8;
	}
	printf("������ �������� %d ���� ����������� \"%s\".\n", Ret, message);
	printf("��������� �'������� � �볺����.\n");
	closesocket(NewConnection);

	// ����������� Winsock
	WSACleanup();
	printf("�������� Enter ��� ����������.\n");
	getchar();
	getchar();

	return 0;
}