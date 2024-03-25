//Device.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Device.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define NULL 0

using namespace std;

CDevice :: CDevice(const char* x, int y, int z)
{
	year = y;
	power = z;
	number_of_model1 = new char[strlen(x) + 1];
	strcpy_s(number_of_model1, strlen(x) + 1, x);
	number_of_model2 = 0;
}



CDevice :: CDevice(CDevice& dev) 
{
	number_of_model1 = dev.number_of_model1;
	number_of_model2 = dev.number_of_model2;
	year = dev.year;
	power = dev.power;
}

CDevice :: ~CDevice()
{
	cout << "Destruktor" << endl;
	if(number_of_model1 != NULL)
		delete[] number_of_model1;
	if (number_of_model2 != NULL)
		delete[] number_of_model2;
}

void CDevice :: Set_All()
{
	this->year = year;
	this->power = power;
}

char* CDevice :: Get_Number() 
{
	return number_of_model1;
}

int CDevice::Get_Year()
{
	return year;
}

int CDevice::Get_Power()
{
	return power;
}

CDevice& CDevice :: operator= (CDevice& obj)
{
	if (&obj == this) // перевірка на самоприсвоєння
	{
		return *this;
	}
	else
	{
		power = obj.power;
		year = obj.year;
	}
	cout << "*******(Operator =)*******" << endl;
	return *this;
}


int CDevice::Devise_Age()
{
	int now = 2022 - year;
	return now;
}

float CDevice :: Device_Power_In_KGz()
{
	float kilo = power / 1000;
	return kilo;
}
