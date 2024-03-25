#include "CEngine.h"
#pragma once
class DieselEngine : public Engine 
{
protected:
	float fuel; // ������ � �����
	float frequency; // ������� (������� ������ �� ������� ������)
public:
	// ������������ � ����������
	DieselEngine(const char* x, float y, float z, float w);
	DieselEngine(const char* x);
	DieselEngine(DieselEngine& die);
	virtual ~DieselEngine();

	// �������� ���������
	DieselEngine& operator= (DieselEngine& obj);

	// ������ (���� � ���� ����������)
	float Get_Fuel();
	float Get_Frequency();
	float Productivity(float fuel_per_hour); // ������ ���� ����� � ����� ������� �������� (������� ������ �������� ����������� �� ������ ������)
	float Speed(float period); // �������� ��������� � ��� �������� (������� ������� �� ����� ���������) (������� ����� � ��������)

	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month);
};