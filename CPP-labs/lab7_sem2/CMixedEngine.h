#include "CGasEngine.h"
#include "CDieselEngine.h"
#pragma once
class MixedEngine : public GasEngine, public DieselEngine
{
private:
	char* name; // ��'� �������
	int number_of_valves; // ������� ������� � �������
public:
	// ������������ � ����������
	MixedEngine(const char* c, const char* x, int d, float y, float z, float w, float a, float b); // i�'�, ���, �-���� �������, ���������, ������, �������, ���, ����
	MixedEngine(const char* c, const char* x); // �� ���� ���������� ����������� (��������� ���� ��'� � ���)
	MixedEngine(MixedEngine& die);
	virtual ~MixedEngine();

	// �������� ���������
	MixedEngine& operator= (MixedEngine& obj);

	// ������
	char* Get_Name();
	int Get_Number_Of_Valves();
	bool Engine_Performance(); // ���� ������� ������� ����� 9, �� ������ ����������� ����
	int Chance_Of_Breakage(); // ��� ����� �������, ��� ����� ���� ������� (����� ������ �� +3% ���� �������)

	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month);
};
