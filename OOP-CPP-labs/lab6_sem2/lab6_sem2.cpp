//main.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "CopyApparat.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main()
{
	// ПЕРШИЙ КОПІЮВАЛЬНИЙ АПАРАТ
	// Ім'я апарата *** Тип моделі *** Рік виготовлення *** Потужність *** Заряд апарата *** Продуктивність аппарата     Year of manufacture
	CCopyApparat Electron("Electron", "TTPS", 1995, 6000, 200, 30);
	// Вивід характеристик пристрою
	cout << "Name of Copy Apparat is " << Electron.Get_Name() << "." << endl;
	cout << "Number of model of " << Electron.Get_Name() << " is " << Electron.Get_Number() << "." << endl;
	cout << "Year of manufacture of " << Electron.Get_Name() << " is " << Electron.Get_Year() << "." << endl;
	cout << "Maximum charge of " << Electron.Get_Name() << " is " << Electron.Get_Charge() << "%." << endl;
	cout << "Power of " << Electron.Get_Name() << " is " << Electron.Get_Power() << " Hertz." << endl;
	cout << "Speed of work (Productivity) of " << Electron.Get_Name() << " is " << Electron.Get_Speed_Of_Work() << " sheets per minute." << endl;
	// Використання методів обробки даних
	cout << Electron.Get_Name() << " will be completely discharged in " << Electron.Discharge_Time() << " hours." << endl;
	cout << "Power of " << Electron.Get_Name() << " in KiloHertz is " << Electron.Device_Power_In_KGz() << "." << endl;
	cout << "The age of " << Electron.Get_Name() << " is " << Electron.Devise_Age() << " year(s)." << endl;
	cout << Electron.Get_Name() << " can process " << Electron.Productivity() << " sheets per hour." << endl;
	cout << "\n";

	// ДРУГИЙ КОПІЮВАЛЬНИЙ АПАРАТ (БЕТА-ВЕРСІЯ ПЕРШОГО(має усі ті самі характеристики))
	// Ім'я апарата *** Тип моделі *** Рік виготовлення *** Потужність *** Заряд апарата *** Продуктивність аппарата     Year of manufacture
	CCopyApparat Electron2("Electron2_BETA", "TTPS");
	Electron2 = Electron;
	// Вивід характеристик пристрою
	cout << "Name of Copy Apparat is " << Electron2.Get_Name() << "." << endl;
	cout << "Number of model of " << Electron2.Get_Name() << " is " << Electron2.Get_Number() << "." << endl;
	cout << "Year of manufacture of " << Electron2.Get_Name() << " is " << Electron2.Get_Year() << "." << endl;
	cout << "Maximum charge of " << Electron2.Get_Name() << " is " << Electron2.Get_Charge() << "%." << endl;
	cout << "Power of " << Electron2.Get_Name() << " is " << Electron2.Get_Power() << " Hertz." << endl;
	cout << "Speed of work (Productivity) of " << Electron2.Get_Name() << " is " << Electron2.Get_Speed_Of_Work() << " sheets per minute." << endl;
	// Використання методів обробки даних
	cout << Electron2.Get_Name() << " will be completely discharged in " << Electron2.Discharge_Time() << " hours." << endl;
	cout << "Power of " << Electron2.Get_Name() << " in KiloHertz is " << Electron2.Device_Power_In_KGz() << "." << endl;
	cout << "The age of " << Electron2.Get_Name() << " is " << Electron2.Devise_Age() << " year(s)." << endl;
	cout << Electron2.Get_Name() << " can process " << Electron2.Productivity() << " sheets per hour." << endl;
	cout << "\n";

	// ТРЕТІЙ КОПІЮВАЛЬНИЙ АПАРАТ (ПО ЗАМОВЧУВАННЮ)
	CCopyApparat Apparat("Simple Copy Apparat", "SCVN");
	// Вивід характеристик пристрою
	cout << "Name of Copy Apparat is " << Apparat.Get_Name() << "." << endl;
	cout << "Number of model of " << Apparat.Get_Name() << " is " << Apparat.Get_Number() << "." << endl;
	cout << "Year of manufacture of " << Apparat.Get_Name() << " is " << Apparat.Get_Year() << "." << endl;
	cout << "Maximum charge of " << Apparat.Get_Name() << " is " << Apparat.Get_Charge() << "%." << endl;
	cout << "Power of " << Apparat.Get_Name() << " is " << Apparat.Get_Power() << " Hertz." << endl;
	cout << "Speed of work (Productivity) of " << Apparat.Get_Name() << " is " << Apparat.Get_Speed_Of_Work() << " sheets per minute." << endl;
	// Використання методів обробки даних
	cout << Apparat.Get_Name() << " will be completely discharged in " << Apparat.Discharge_Time() << " hours." << endl;
	cout << "Power of " << Apparat.Get_Name() << " in KiloHertz is " << Apparat.Device_Power_In_KGz() << "." << endl;
	cout << "The age of " << Apparat.Get_Name() << " is " << Apparat.Devise_Age() << " year(s)." << endl;
	cout << Apparat.Get_Name() << " can process " << Apparat.Productivity() << " sheets per hour." << endl;
	cout << "\n";
	return 0;
}
