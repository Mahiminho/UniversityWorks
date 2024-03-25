// Array.cpp: implementation of the Array class.
#include "Array.h"
Array::Array(int s)
{
	size = s;
	ptr = new int[size];
	for (int i = 0; i < size; i++)
	{
		ptr[i] = 0;
	}
	cout << "Constructor" << endl;
}
//----------------------------------------------------------------------
Array::Array(Array& arr)
{
	size = arr.size;
	ptr = new int[size];
	for (int i = 0; i < size; i++)
	{
		ptr[i] = arr.ptr[i];
	}
	cout << "Copy Constructor" << endl;
}
//----------------------------------------------------------------------
Array::~Array()
{
	delete[] ptr;
	cout << "Destructor" << endl;
}
//----------------------------------------------------------------------
void Array::Rindomize(int num)
{
	for (int i = 0; i < size; i++)
	{
		ptr[i] = rand() % num;
	}
}
//----------------------------------------------------------------------
ostream & operator<< (ostream & output, Array & arr)
{
	for (int i = 0; i < arr.size; i++)
	{
		output << arr.ptr[i] << " ";
	}
	output << endl;
	return output;
}
//----------------------------------------------------------------------
Array& Array::operator= (Array& arr)
{
	if (this != &arr)
	{
		delete[] ptr;
		size = arr.size;
		ptr = new int[size];
		for (int i = 0; i < size; i++)
		{
			ptr[i] = arr.ptr[i];
		}
	}
	cout << "Operator =" << endl;
	return *this;
}
//----------------------------------------------------------------------
int Array::operator!= (Array& arr)
{
	if (size != arr.size)
		return 1;
	for (int i = 0; i < size; i++)
	{
		if (ptr[i] != arr.ptr[i])
			return 1;
	}
	return 0;
}
//----------------------------------------------------------------------
Array Array::operator+ (Array& arr)
{
	int mins = (size < arr.size) ? size : arr.size;
	Array temp;
	if (mins == arr.size)
	{
			temp = *this;
		for (int i = 0; i < mins; i++)
		{
			temp.ptr[i] += arr.ptr[i];
		}
	}
	else
	{
		temp = arr;
		for (int i = 0; i < mins; i++)
		{
			temp.ptr[i] += ptr[i];
		}
	}
	cout << "Operator +" << endl;
	return temp;
}
//----------------------------------------------------------------------
Array& Array::operator+= (Array& arr)
{
	Array temp;
	//temp = *this + arr;
	*this = temp;
	return *this;
}
//----------------------------------------------------------------------
Array Array::operator++ ()
{
	for (int i = 0; i < size; i++)
		ptr[i] += 1;
	return *this;
}
//----------------------------------------------------------------------
Array Array::operator++ (int)
{
	Array temp = *this;
	for (int i = 0; i < size; i++)
		ptr[i] += 1;
	return temp;
}