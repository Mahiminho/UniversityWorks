#include "CMixedEngine.h"
#include <iostream>
#include <stdlib.h>
#define NULL 0

using namespace std;

MixedEngine::MixedEngine(const char* c, const char* x, int d, float y, float z, float w, float a, float b) : GasEngine(x, y, a, b), DieselEngine(x, y, z, w)
{
	type1 = new char[strlen(x) + 1];
	strcpy_s(type1, strlen(x) + 1, x);
	name = new char[strlen(c) + 1];
	strcpy_s(name, strlen(c) + 1, c);
	power1 = y;
	fuel = z;
	frequency = w;
	volume = a;
	weight = b;
	number_of_valves = d;
}

MixedEngine::MixedEngine(const char* c, const char* x) : GasEngine(x), DieselEngine(x)
{
	type1 = new char[strlen(x) + 1];
	strcpy_s(type1, strlen(x) + 1, x);
	name = new char[strlen(c) + 1];
	strcpy_s(name, strlen(c) + 1, c);
	this->power1 = power1;
	this->fuel = fuel;
	this->frequency = frequency;
	this->volume = volume;
	this->weight = weight;
	this->number_of_valves = number_of_valves;
}

MixedEngine::MixedEngine(MixedEngine& die) : GasEngine(die), DieselEngine(die)
{
	power1 = die.power1;
	volume = die.volume;
	weight = die.weight;
	fuel = die.fuel;
	frequency = die.frequency;
	number_of_valves = die.number_of_valves;
}

MixedEngine::~MixedEngine()
{
	cout << "Destructor" << endl;
	if (name != NULL)
		delete name;
}

MixedEngine& MixedEngine :: operator= (MixedEngine& die)
{
	if (&die == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		power1 = die.power1;
		volume = die.volume;
		weight = die.weight;
		fuel = die.fuel;
		frequency = die.frequency;
		number_of_valves = die.number_of_valves;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}

char* MixedEngine::Get_Name()
{
	return name;
}

int MixedEngine::Get_Number_Of_Valves()
{
	return number_of_valves;
}

bool MixedEngine::Engine_Performance()
{
	if (number_of_valves < 9)
		return false;
	else
		return true;
}

int MixedEngine::Chance_Of_Breakage()
{
	int chance = number_of_valves * 3;
	return chance;
}


char* MixedEngine::Get_Type()
{
	return type1;
}

float MixedEngine::Get_Power()
{
	return power1;
}

float MixedEngine::Years_Working(float power_month)
{
	float years = power1 / (power_month * 12);
	return years;
}