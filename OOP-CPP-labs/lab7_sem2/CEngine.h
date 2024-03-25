#pragma once
class Engine
{
protected:
	char* type; // тип двигуна
	float power; // потужн≥сть у ватах
public:
	// конструктори ≥ деструктор
	Engine(const char* x, float y);
	Engine(const char* x);
	Engine(Engine& eng);
	virtual ~Engine();

	// оператор присвоЇнн€
	Engine& operator= (Engine& obj);

	// методи (один з €ких в≥ртуальний)
	virtual char* Get_Type();
	virtual float Get_Power();
	virtual float Years_Working(float power_month); // вводимо ск≥льки потужност≥ (у ватах) втрачатиме двигун за м≥с€ць, а метод повертаЇ ск≥льки рок≥в працюватиме двигун, поки не знищитьс€
};