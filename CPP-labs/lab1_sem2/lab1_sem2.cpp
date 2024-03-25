#include <iostream>
#include <cmath>

using namespace std;

bool func(int* arr, int length);
bool func(char* str);

int main(void)
{
    
    const int size = 10;
    static char str[256] = "trabcdezo";
    register int arr[size] = { 8, 0, 7, 6, 5, 4, 3, 2, 19, 9 };
    cout << "Array: ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    cout << "String: " << str << endl;
    //cout << "\nEnter the string: ";
    //cin >> str;
    cout << "Elements of array" << (func(arr, size) ? " are" : " aren't") << " arranged in ascending order." << endl;
    cout << "Elements of string" << (func(str) ? " are" : " aren't") << " arranged in ascending order." << endl;
}

bool func(int* arr, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return true;
        }
    }

    return false;
}

bool func(char* str)
{
    int i;
    for (i = 0; i < (strlen(str) - 1); i++)
    {
        if (str[i] > str[i + 1])
        {
            return false;
        }
    }
    return true;
}

