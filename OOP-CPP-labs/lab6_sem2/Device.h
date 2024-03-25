// Device.h
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class CDevice
{
protected:
	char* number_of_model1;
	char* number_of_model2;
	int year;
	int power;
public:
	// конструктор по замовчуванню (не успадковується)
	CDevice(const char* x, int y = 2000, int z = 11000);

	// конструктор копіювання 
	CDevice(CDevice& dev);

	// віртуальний деструктор
	virtual ~CDevice();

	// перевантаження оператора (=)
	CDevice& operator= (CDevice& obj);

	// Set i Get
	void Set_All();
	char* Get_Number();
	int Get_Year();
	int Get_Power();

	// Методи обробки данних
	int Devise_Age();
	float Device_Power_In_KGz();
};