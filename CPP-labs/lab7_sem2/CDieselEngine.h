#include "CEngine.h"
#pragma once
class DieselEngine : public Engine 
{
protected:
	float fuel; // пальне в літрах
	float frequency; // частота (кількість обертів за хвилину роботи)
public:
	// конструктори і деструктор
	DieselEngine(const char* x, float y, float z, float w);
	DieselEngine(const char* x);
	DieselEngine(DieselEngine& die);
	virtual ~DieselEngine();

	// оператор присвоєння
	DieselEngine& operator= (DieselEngine& obj);

	// методи (один з яких віртуальний)
	float Get_Fuel();
	float Get_Frequency();
	float Productivity(float fuel_per_hour); // скільки часу проїде з такою кількості пального (вводимо скільки пального витрачатиме за годину роботи)
	float Speed(float period); // швидкість автомобіля з цим двигуном (частота поділена на період обертання) (вводимо період у хвилинах)

	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month);
};