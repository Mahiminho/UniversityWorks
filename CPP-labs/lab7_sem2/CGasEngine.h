#include "CEngine.h"
#pragma once
class GasEngine : public Engine
{
protected:
	float volume; // об'єм в літрах
	float weight; // вага в кілограмах
	char* type1 = Engine::type;
	float power1 = Engine::power;
public:
	// конструктори і деструктор
	GasEngine(const char* x, float y, float a, float b);
	GasEngine(const char* x);
	GasEngine(GasEngine& die);
	virtual ~GasEngine();

	// оператор присвоєння
	GasEngine& operator= (GasEngine& obj);

	// методи
	float Get_Volume();
	float Get_Weight();
	float Money_GasEngine(float price_of_kg); // підраховує ціну матеріалів витрачених на виготовлення двигуна (ми вводимо ціну за 1 кг)
	float Distance(float gas_in_kilometr); // підраховує дистанцію яку проїде автомобіль з таким двигуном (вводимо скільки літрів гасу потрібно для проїзду одного км)
};