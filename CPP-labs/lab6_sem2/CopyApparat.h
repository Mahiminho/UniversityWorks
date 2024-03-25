//CCopyApparat.h
#define _CRT_SECURE_NO_WARNINGS
#include "Device.h"
#include <iostream>

using namespace std;

class CCopyApparat : public CDevice
{
private:
	int charge;
	int speed_of_work; // ������� ������ �� ������� (������ �������� �������) (���������Ͳ���)
	char* name1;
	char* name2;
public:
	// ����������� �� ������������
	CCopyApparat(const char* c, const char* x, int y = 2000, int z = 11000, int a = 100, int b = 50);

	// ����������� ��������� 
	CCopyApparat(CCopyApparat& app);

	// ���������� ����������
	virtual ~CCopyApparat();

	// �������������� ��������� (=)
	CCopyApparat& operator= (CCopyApparat& obj);

	// Set i Get
	void Set_ALL();
	int Get_Charge();
	int Get_Speed_Of_Work();
	char* Get_Name();

	// ������ ������� ������
	float Discharge_Time();// ����� ������ -10% ������, ������� ������� ������ ����� ����, ��� ������� ��������� �������
	int Productivity(); // ������� ���������� ������ �� ������
};