// Rectangle.cpp: implementation of the Rectangle class.
#include "Rectangle.h"

using namespace std;

CHuman::CHuman(int x, int y, int z, int w)
{
	year = x;
	age = y;
	number_of_skills = z;
	salary = w;
}

CHuman::CHuman(const CHuman& hum)
{
	year = hum.year;
	age = hum.age;
	number_of_skills = hum.number_of_skills;
	salary = hum.salary;
}

CHuman::~CHuman()
{
}

int CHuman::GetYear()
{
	return year;
}

int CHuman::GetAge()
{
	return age;
}

int CHuman::GetNumber_of_skills() 
{
	return number_of_skills;
}

int CHuman::GetSalary()
{
	return salary;
}

int CHuman::NowAge(int now_year)
{
	int age1 = now_year - year;
	return age1;
}

int CHuman::NowNumber_of_skills(int now_year)
{
	int number_of_skills1 = (now_year - year) / 2.5;
	return number_of_skills1;
}

double CHuman::NowSalary(int now_year)
{
	double salary1 = ((now_year - year) / 2.5) * 1000;
	return salary1;
}
double CHuman::Time_for_sum(int sum, int now_year) 
{
	double time = sum / (((now_year - year) / 2.5) * 1000);
	return time;
}
