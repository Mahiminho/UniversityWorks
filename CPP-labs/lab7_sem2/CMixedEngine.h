#include "CGasEngine.h"
#include "CDieselEngine.h"
#pragma once
class MixedEngine : public GasEngine, public DieselEngine
{
private:
	char* name; // ім'я двигуна
	int number_of_valves; // кількість клапанів в двигуна
public:
	// конструктори і деструктор
	MixedEngine(const char* c, const char* x, int d, float y, float z, float w, float a, float b); // iм'я, тип, к-кість клапанів, потужність, пальне, частота, обєм, вага
	MixedEngine(const char* c, const char* x); // ще один додатковий конструктор (вказувати лише ім'я і тип)
	MixedEngine(MixedEngine& die);
	virtual ~MixedEngine();

	// оператор присвоєння
	MixedEngine& operator= (MixedEngine& obj);

	// методи
	char* Get_Name();
	int Get_Number_Of_Valves();
	bool Engine_Performance(); // якщо кількість клапанів менше 9, то двигун працюватиме гірше
	int Chance_Of_Breakage(); // чим менше клапанів, тим менше шанс поломки (кожен клапан це +3% шанс поломки)

	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month);
};
