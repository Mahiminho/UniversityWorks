// Rectangle.h: interface for the Rectangle class.
#include <iostream> 
using namespace std;
class CHuman
{
private:
	int year;
	int age;
	int number_of_skills;
	int salary;
public:
	// конструктор за замовчуванням
	CHuman(int x = 2002, int y = 20, int z = 8, int w = 8000);
	// конструктор копіювання
	CHuman(const CHuman& hum);
	// деструктор
	virtual ~CHuman();
	// функції повернення
	int GetYear();
	int GetAge();
	int GetNumber_of_skills();
	int GetSalary();
	// функції обробки данних
	int NowAge(int now_year);
	int NowNumber_of_skills(int now_year);
	double NowSalary(int now_year);
	double Time_for_sum(int sum, int now_year);
	// перевантаження операторів
	friend ostream& operator<< (ostream& output, CHuman& obj);
	friend istream& operator>> (istream& input, CHuman& obj);
	CHuman& operator= (CHuman& obj);
	CHuman& operator* (CHuman& obj);
	CHuman& operator+= (CHuman& obj);
	bool operator> (CHuman& obj);
	bool operator< (CHuman& obj);
};

