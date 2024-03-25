#include "CEngine.h"
#pragma once
class GasEngine : public Engine
{
protected:
	float volume; // ��'�� � �����
	float weight; // ���� � ���������
	char* type1 = Engine::type;
	float power1 = Engine::power;
public:
	// ������������ � ����������
	GasEngine(const char* x, float y, float a, float b);
	GasEngine(const char* x);
	GasEngine(GasEngine& die);
	virtual ~GasEngine();

	// �������� ���������
	GasEngine& operator= (GasEngine& obj);

	// ������
	float Get_Volume();
	float Get_Weight();
	float Money_GasEngine(float price_of_kg); // �������� ���� �������� ���������� �� ������������ ������� (�� ������� ���� �� 1 ��)
	float Distance(float gas_in_kilometr); // �������� ��������� ��� ����� ��������� � ����� �������� (������� ������ ���� ���� ������� ��� ������ ������ ��)
};