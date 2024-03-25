// Array.h: interface for the Array class.
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
class Array
{
	int* ptr;
	int size;
public:
	Array(int s = 10);
	Array(Array& arr);
	virtual ~Array();
	friend ostream& operator<< (ostream& output, Array& arr);
	void Rindomize(int num = 10);
	Array& operator= (Array& arr);
	Array& operator+= (Array& arr);
		Array operator+ (Array & arr);
	int operator!= (Array& arr);
	Array operator++ ();
	Array operator++ (int);
};