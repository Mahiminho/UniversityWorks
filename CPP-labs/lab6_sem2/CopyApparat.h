//CCopyApparat.h
#define _CRT_SECURE_NO_WARNINGS
#include "Device.h"
#include <iostream>

using namespace std;

class CCopyApparat : public CDevice
{
private:
	int charge;
	int speed_of_work; // кількість листків за хвилину (скільки обробляє аппарат) (ПРОДУКТИВНІСТЬ)
	char* name1;
	char* name2;
public:
	// конструктор по замовчуванню
	CCopyApparat(const char* c, const char* x, int y = 2000, int z = 11000, int a = 100, int b = 50);

	// конструктор копіювання 
	CCopyApparat(CCopyApparat& app);

	// віртуальний деструктор
	virtual ~CCopyApparat();

	// перевантаження оператора (=)
	CCopyApparat& operator= (CCopyApparat& obj);

	// Set i Get
	void Set_ALL();
	int Get_Charge();
	int Get_Speed_Of_Work();
	char* Get_Name();

	// Методи обробки данних
	float Discharge_Time();// кожну годину -10% заряду, функція визначає скільки треба часу, щоб повністю розрядити пристрій
	int Productivity(); // кількість оброблених листків за годину
};