// main.cpp
#include <fstream>
#include <string>
#include <iomanip>
#include<iostream>
#include"Rectangle.h"

using namespace std;

int main()
{
	while (true) {
		cout << "--------MENU--------" << endl;
		cout << "Show data - press 1" << endl;
		cout << "Write data - press 2" << endl;
		cout << "Exit - press 3" << endl;
		cout << "Operators overload - press 4" << endl;
		int choose;
		cin >> choose;

		if (choose == 1)
		{
			ifstream infile;
			infile.open("File.txt");

			if (!infile)
			{
				cout << "Cannot open file" << endl;
				return -1;
			}

			if (!infile.eof())
			{
				// перша людина
				CHuman Olga;
				cout << "Olga" << endl;
				cout << "Year of birth: " << Olga.GetYear() << endl;
				cout << "Age: " << Olga.GetAge() << endl;
				cout << "Number of skills: " << Olga.GetNumber_of_skills() << endl;
				cout << "Salary for month: " << Olga.GetSalary() << endl;

				//  друга людина
				CHuman Oleg(1997, 25, 10, 10000);
				cout << "Oleg" << endl;
				cout << "Year of birth: " << Oleg.GetYear() << endl;
				cout << "Age: " << Oleg.GetAge() << endl;
				cout << "Number of skills: " << Oleg.GetNumber_of_skills() << endl;
				cout << "Salary for month: " << Oleg.GetSalary() << endl;
				// третя людина (брат-близнюк Олега)
				CHuman Ivan(Oleg);
				cout << "Ivan" << endl;
				cout << "Year of birth: " << Ivan.GetYear() << endl;
				cout << "Age: " << Ivan.GetAge() << endl;
				cout << "Number of skills: " << Ivan.GetNumber_of_skills() << endl;
				cout << "Salary for month: " << Ivan.GetSalary() << endl;
				cout << endl;
			}

			infile.close();
		}

		if (choose == 2)
		{
			cout << "Enter year: ";
			int now_year;
			cin >> now_year;
			cout << "Enter sum of money: ";
			int sum;
			cin >> sum;

			fstream outfile("File.txt", ios::app);

			if (!outfile)
			{
				cout << "Cannot open file" << endl;
				return -1;
			}

			CHuman Olga;
			cout << "Olga" << endl;
			cout << "Year of birth: " << Olga.GetYear() << endl;
			cout << "In this year age: " << Olga.NowAge(now_year) << endl;
			cout << "In this year number of skills: " << Olga.NowNumber_of_skills(now_year) << endl;
			cout << "In this year salary: " << Olga.NowSalary(now_year) << endl;
			cout << "She must working " << Olga.Time_for_sum(sum, now_year) << " years, if she want to get " << sum << endl;
			outfile << "Olga" << endl;
			outfile << "Year of birth: " << Olga.GetYear() << endl;
			outfile << "In this year age: " << Olga.NowAge(now_year) << endl;
			outfile << "In this year number of skills: " << Olga.NowNumber_of_skills(now_year) << endl;
			outfile << "In this year salary: " << Olga.NowSalary(now_year) << endl;
			outfile << "She must working " << Olga.Time_for_sum(sum, now_year) << " years, if she want to get " << sum << endl;

			CHuman Oleg(1997, 25, 10, 10000);
			cout << "Oleg" << endl;
			cout << "Year of birth: " << Oleg.GetYear() << endl;
			cout << "In this year age: " << Oleg.NowAge(now_year) << endl;
			cout << "In this year number of skills: " << Oleg.NowNumber_of_skills(now_year) << endl;
			cout << "In this year salary: " << Oleg.NowSalary(now_year) << endl;
			cout << "He must working " << Oleg.Time_for_sum(sum, now_year) << " years, if he want to get " << sum << endl;
			outfile << "Oleg" << endl;
			outfile << "Year of birth: " << Oleg.GetYear() << endl;
			outfile << "In this year age: " << Oleg.NowAge(now_year) << endl;
			outfile << "In this year number of skills: " << Oleg.NowNumber_of_skills(now_year) << endl;
			outfile << "In this year salary: " << Oleg.NowSalary(now_year) << endl;
			outfile << "He must working " << Oleg.Time_for_sum(sum, now_year) << " years, if he want to get " << sum << endl;
			Oleg = Olga;
			CHuman Ivan(Oleg);
			cout << "Ivan" << endl;
			cout << "Year of birth: " << Ivan.GetYear() << endl;
			cout << "In this year age: " << Ivan.NowAge(now_year) << endl;
			cout << "In this year number of skills: " << Ivan.NowNumber_of_skills(now_year) << endl;
			cout << "In this year salary: " << Ivan.NowSalary(now_year) << endl;
			cout << "He must working " << Ivan.Time_for_sum(sum, now_year) << " years, if he want to get " << sum << endl;
			outfile << "Ivan" << endl;
			outfile << "Year of birth: " << Ivan.GetYear() << endl;
			outfile << "In this year age: " << Ivan.NowAge(now_year) << endl;
			outfile << "In this year number of skills: " << Ivan.NowNumber_of_skills(now_year) << endl;
			outfile << "In this year salary: " << Ivan.NowSalary(now_year) << endl;
			outfile << "He must working " << Ivan.Time_for_sum(sum, now_year) << " years, if he want to get " << sum << endl;
			outfile << endl;
			cout << endl;
			outfile.close();

			// перевантаження операторів
			/*
			cout << "Enter random number" << endl;
			CHuman num, num2 = 10;
			cin >> num;
			*/
		}

		if (choose == 3)
		{
			break;
		}


		if (choose == 4) 
		{
			CHuman Olga(1992, 30, 12, 12000);
			cout << "Olga" << endl;
			cout << "Year of birth: " << Olga.GetYear() << endl;
			cout << "Age: " << Olga.GetAge() << endl;
			cout << "Number of skills: " << Olga.GetNumber_of_skills() << endl;
			cout << "Salary for month: " << Olga.GetSalary() << endl;

			CHuman Olena;
			Olena = Olga;
			cout << "Olena" << endl;
			cout << "Year of birth: " << Olena.GetYear() << endl;
			cout << "Age: " << Olena.GetAge() << endl;
			cout << "Number of skills: " << Olena.GetNumber_of_skills() << endl;
			cout << "Salary for month: " << Olena.GetSalary() << endl;
			
			CHuman Oleg;
			Oleg = Oleg * Olga;
			cout << "Oleg" << endl;
			cout << "Year of birth: " << Oleg.GetYear() << endl;
			cout << "Age: " << Oleg.GetAge() << endl;
			cout << "Number of skills: " << Oleg.GetNumber_of_skills() << endl;
			cout << "Salary for month: " << Oleg.GetSalary() << endl;
			
			CHuman Ivan;
			Ivan += Olga;
			cout << "Ivan" << endl;
			cout << "Year of birth: " << Ivan.GetYear() << endl;
			cout << "Age: " << Ivan.GetAge() << endl;
			cout << "Number of skills: " << Ivan.GetNumber_of_skills() << endl;
			cout << "Salary for month: " << Ivan.GetSalary() << endl;

			if (Oleg > Ivan)
				cout << "Oleg is better" << endl;
			else
				cout << "Ivan is better" << endl;


			if (Olga < Olena)
				cout << "Olena is better" << endl;
			else
				cout << "Olga is better" << endl;
			
			cin >> Oleg;
			
			cout << Oleg;

		}
	}
	system("pause");
}

