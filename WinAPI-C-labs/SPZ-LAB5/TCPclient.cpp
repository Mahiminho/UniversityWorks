// TCP �볺��
#pragma comment(lib, "Ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	printf("TCP �볺�� \n");
	printf("___________\n\n");
	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in ServerAddr, ca;
	u_short Port = 5150;
	int Ret;
	char DataBuffer[1024];
	int caSize = sizeof(ca);

	// ����������� Winsock ���� 2.2
	if ((Ret = WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		//Winsock �� ������������. ��� ������� ������� ������� WSAStartup
		printf("������� WSAStartup, ����� ������� %d\n", Ret);
		return 1;
	}

	// �������� ����� ����� ��� �'������� ����� TCP �볺���
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET) {
		printf("������� socket, ����� ������� %d\n", WSAGetLastError());
		WSACleanup();
		return 2;
	}

	// ��������� � ����� ServerAddr ������� ���������� ��� ������, �� ����� �� ������ �����������.
	// ������ ����� ���� 5150, IP-������ ������� ������� � ���������
	char ipAddress[32];
	printf("������ IP - ������ ������� : ");
	gets_s(ipAddress);
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = inet_addr(ipAddress);

	// �'������ ����� s � ��������
	printf("������ �'������� � %s : %d ...\n", inet_ntoa(ServerAddr.sin_addr), htons(ServerAddr.sin_port));
	if (connect(s, (struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		printf("������� connect, ����� ������� %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 3;
	}
	printf("�'������� ������.\n");

	// �������� ���������� ��� ������ �� ���� �볺���
	getsockname(s, (struct sockaddr*)&ca, &caSize);
	printf("������ � ���� ����� %s : %d \n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port));

	// ����� �� ������ ����������� ������ � �������� ����� ����� s
	int num;
	char str[4];
	printf("������ ����� �������: ");
	scanf_s("%d", &num);
	sprintf_s(str, "%d", num);
	const char* message = str;
	printf("������ �������� �����������.\n");
	if ((Ret = send(s, message, sizeof(message), 0)) == SOCKET_ERROR) {
		printf("������� send, ����� ������� %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 4;
	}
	printf("������ �������� %d ���� ����������� \"%s\".\n", Ret, message);

	// �������� ��� �� �������
	printf("������ ��� ��� ���������...\n");
	if ((Ret = recv(s, DataBuffer, sizeof(DataBuffer), 0)) == SOCKET_ERROR) {
		printf("������� recv, ����� ������� %d\n", WSAGetLastError());
		closesocket(s);
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
	printf("������ �������� %d ���� � ���������� \"%s\".\n", Ret, DataBuffer);
	printf("��������� �'������� � ��������.\n");
	closesocket(s);

	// ����������� Winsock
	WSACleanup();
	printf("�������� Enter ��� ����������.\n");
	getchar();
	getchar();

	return 0;
}