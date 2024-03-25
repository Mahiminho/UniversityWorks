#include <iostream>
#include "CDieselEngine.h"

using namespace std;

DieselEngine :: DieselEngine(const char* x, float y, float z, float w) : Engine(x, y)
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
	power = y;
	fuel = z;
	frequency = w;
}

DieselEngine::DieselEngine(const char* x) : Engine(x)
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
}

DieselEngine::DieselEngine(DieselEngine& die) : Engine(die)
{
	power = die.power;
	fuel = die.fuel;
	frequency = die.frequency;
}

DieselEngine :: ~DieselEngine()
{

}

DieselEngine& DieselEngine :: operator= (DieselEngine& obj)
{
	if (&obj == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		power = obj.power;
		fuel = obj.fuel;
		frequency = obj.frequency;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}

float DieselEngine::Get_Fuel()
{
	return fuel;
}

float DieselEngine::Get_Frequency()
{
	return frequency;
}

float DieselEngine::Productivity(float fuel_per_hour)
{
	float time = fuel / fuel_per_hour;
	return time;
}

float DieselEngine::Speed(float period)
{
	float speed = frequency / period;
	return speed;
}


char* DieselEngine::Get_Type()
{
	return type;
}

float DieselEngine::Get_Power()
{
	return power;
}

float DieselEngine::Years_Working(float power_month)
{
	float years = power / (power_month * 12);
	return years;
}