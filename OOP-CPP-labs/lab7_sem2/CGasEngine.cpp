#include <iostream>
#include "CGasEngine.h"

using namespace std;

GasEngine::GasEngine(const char* x, float y, float a, float b) : Engine(x, y)
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
	power = y;
	volume = a;
	weight = b;
}

GasEngine::GasEngine(const char* x) : Engine(x)
{
	type = new char[strlen(x) + 1];
	strcpy_s(type, strlen(x) + 1, x);
}

GasEngine::GasEngine(GasEngine& die) : Engine(die)
{
	power = die.power;
	volume = die.volume;
	weight = die.weight;
}

GasEngine :: ~GasEngine()
{

}

GasEngine& GasEngine :: operator= (GasEngine& obj)
{
	if (&obj == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		power = obj.power;
		volume = obj.volume;
		weight = obj.weight;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}

float GasEngine::Get_Volume()
{
	return volume;
}

float GasEngine::Get_Weight()
{
	return weight;
}

float GasEngine::Money_GasEngine(float price_of_kg)
{
	float money = weight * price_of_kg;
	return money;
}

float GasEngine::Distance(float gas_in_kilometr)
{
	float distance = volume * gas_in_kilometr;
	return distance;
}