// З клавіатури вводиться назва авіалінії, кількість клієнтів в день і ціна білету, а назва аліалінії, кількість клієнтів в місяць і прибуток в місяць записуються у файл.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


int main()
{
	while (true)
	{
		cout << "Show data - press 1" << endl;
		cout << "Write data - press 2" << endl;
		cout << "Exit - press 3" << endl;

		int choice;
		cin >> choice;



		if (choice == 1)
		{
			string avialine;
			int clients;
			double money;
			int clients_in_month;
			double money_in_month;
			ifstream infile;
			infile.open("File.txt");

			if (!infile)
			{
				cout << "Cannot open file" << endl;
				return -1;
			}

			cout << setw(15) << "Avialine " << setw(20) << "Clients in month " << setw(15) << "Money in month" << endl;

			while (!infile.eof())
			{

				infile >> avialine;
				infile >> clients;
				infile >> money;

				if (!infile.eof())
				{
					clients_in_month = clients * 30;
					money_in_month = money * clients_in_month;
					cout.width(15);
					cout << avialine;
					cout.width(15);
					cout << clients_in_month;
					cout.width(15);
					cout << money_in_month;
					cout << endl;
				}

			}

			infile.close();

		}

		if (choice == 2)
		{
			string avialine;
			int clients;
			double money;
			cout << "Enter name of avialine: ";
			cin >> avialine;
			cout << "Enter number of clients in day: ";
			cin >> clients;
			cout << "Enter price of one ticket: ";
			cin >> money;
			fstream outfile("File.txt", ios::app);

			if (!outfile)
			{
				cout << "Cannot open file" << endl;
				return -1;
			}

			outfile.setf(ios::left);
			outfile.width(9);
			outfile << avialine << ' ';
			outfile.width(9);
			outfile << clients << ' ';
			outfile.width(9);
			outfile << money << endl;
			outfile.close();

		}

		if (choice == 3)
		{
			break;
		}

	}

	system("pause");
}

