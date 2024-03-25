#include <iostream>
#include <stdlib.h>
#include "CMixedEngine.h"

using namespace std;

int main()
{
	float power_month, fuel_per_hour, period, price_of_kg, gas_in_kilometr;
	cout << "Enter how much power the engine will lose in a month: " << endl;
	cin >> power_month;
	cout << "Enter how much fuel the engine will consume per hour of operation: " << endl;
	cin >> fuel_per_hour;
	cout << "Enter the engine run period in minutes: " << endl;
	cin >> period; // оптимально буде +- 4 хв
	cout << "Enter the price of one kilogram of engine materials in dollars: " << endl;
	cin >> price_of_kg;
	cout << "Enter how many liters of gas you need to travel 1 kilometer: " << endl;
	cin >> gas_in_kilometr;


	cout << endl;
	// ПЕРШИЙ ДВИГУН
	MixedEngine Engine1("Rogers", "TTUI-558", 10, 15000, 100, 600, 200, 250);
	cout << "<<<Engine 1>>>" << endl;
	cout << "Name: " << Engine1.Get_Name() << "." << endl;
	cout << "Type: " << Engine1.Get_Type() << "." << endl;
	cout << "Number of valves: " << Engine1.Get_Number_Of_Valves() << "." << endl;
	cout << "Power: " << Engine1.Get_Power() << "." << endl;
	cout << "Fuel: " << Engine1.Get_Fuel() << "." << endl;
	cout << "Frequency: " << Engine1.Get_Frequency() << "." << endl;
	cout << "Volume: " << Engine1.Get_Volume() << "." << endl;
	cout << "Weight: " << Engine1.Get_Weight() << "." << endl;
	cout << Engine1.Get_Name() << " engine will run " << Engine1.Years_Working(power_month) << " year(s)." << endl;
	cout << "If you fill " << Engine1.Get_Name() << " engine with " << Engine1.Get_Fuel() << " liters of fuel, the car will travel " << Engine1.Productivity(fuel_per_hour) << " hour(s)." << endl;
	cout << "The speed of a car with " << Engine1.Get_Name() << " engine is " << Engine1.Speed(period) << " km per hour." << endl;
	cout << "The price of " << Engine1.Get_Name() << " engine materials is " << Engine1.Money_GasEngine(price_of_kg) << " dollar(s)." << endl;
	cout << "The car with " << Engine1.Get_Name() << " engine will be able to pass the maximum " << Engine1.Distance(gas_in_kilometr) << " kilometer(s)." << endl;
	cout << "With " << Engine1.Get_Number_Of_Valves() << " valves, " << Engine1.Get_Name() << " engine " << (Engine1.Engine_Performance() ? "will" : "will not") << " run better." << endl;
    cout << "The chance of " << Engine1.Get_Name() << " engine failure is " << Engine1.Chance_Of_Breakage() << "%.";
    cout << endl;
	return 0;
}