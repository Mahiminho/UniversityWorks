#include "CEngine.h"
#include <iostream>
#include <stdlib.h>
#define NULL 0

using namespace std;

Engine::Engine(const char* x, float y) 
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
	power = y;
}

Engine::Engine(const char* x)
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
}

Engine :: Engine(Engine& eng)
{
	power = eng.power;
}

Engine :: ~Engine() 
{
	cout << "Destruktor" << endl;
	if (type != NULL)
		delete[] type;
}

Engine& Engine :: operator= (Engine& obj)
{
	if (&obj == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		power = obj.power;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}

char* Engine :: Get_Type()
{
	return type;
}

float Engine :: Get_Power()
{
	return power;
}

float Engine::Years_Working(float power_month)
{
	float years = power / (power_month * 12);
	return years;
}