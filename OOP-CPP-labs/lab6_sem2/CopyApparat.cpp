//CopyApparat.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "CopyApparat.h"
#include <iostream>
#include <stdlib.h>
#define NULL 0

using namespace std;


CCopyApparat::CCopyApparat(const char* c, const char* x, int y, int z, int a, int b) : CDevice(x, y, z)
{
	charge = a;
	speed_of_work = b;
	year = y;
	power = z;
	number_of_model1 = new char[strlen(x) + 1];
	strcpy_s(number_of_model1, strlen(x) + 1, x);
	number_of_model2 = 0;
	name1 = new char[strlen(c) + 1];
	strcpy_s(name1, strlen(c) + 1, c);
	name2 = 0;
}

CCopyApparat :: CCopyApparat(CCopyApparat& app) : CDevice(app)
{
	charge = app.charge;
	speed_of_work = app.speed_of_work;
	name1 = app.name1;
	name2 = app.name2;
}

CCopyApparat::~CCopyApparat()
{
	cout << "Destruktor" << endl;
	if (name1 != NULL)
		delete[] name1;
	if (name2 != NULL)
		delete[] name2;
}

CCopyApparat& CCopyApparat :: operator= (CCopyApparat& obj)
{
	if (&obj == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		charge = obj.charge;
		speed_of_work = obj.speed_of_work;
		power = obj.power;
		year = obj.year;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}

void CCopyApparat::Set_ALL()
{
	this->charge = charge;
	this->speed_of_work = speed_of_work; 
}

int CCopyApparat::Get_Charge()
{
	return charge;
}

int CCopyApparat::Get_Speed_Of_Work()
{
	return speed_of_work;
}

char* CCopyApparat::Get_Name()
{
	return name1;
}

float CCopyApparat::Discharge_Time()
{
	float time = charge / 10;
	return time;
}

int CCopyApparat::Productivity()
{
	int num = speed_of_work * 60;
	return num;
}