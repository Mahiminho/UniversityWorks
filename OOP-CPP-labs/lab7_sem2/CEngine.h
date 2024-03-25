#pragma once
class Engine
{
protected:
	char* type; // ��� �������
	float power; // ��������� � �����
public:
	// ������������ � ����������
	Engine(const char* x, float y);
	Engine(const char* x);
	Engine(Engine& eng);
	virtual ~Engine();

	// �������� ���������
	Engine& operator= (Engine& obj);

	// ������ (���� � ���� ����������)
	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month); // ������� ������ ��������� (� �����) ���������� ������ �� �����, � ����� ������� ������ ���� ����������� ������, ���� �� ���������
};