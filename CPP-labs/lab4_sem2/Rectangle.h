// Rectangle.h: interface for the Rectangle class.
class CHuman
{
private:
	int year;
	int age;
	int number_of_skills;
	int salary;
public:
	// ����������� �� �������������
	CHuman(int x = 2002, int y = 20, int z = 8, int w = 8000);
	// ����������� ���������
	CHuman(const CHuman& hum);
	// ����������
	virtual ~CHuman();
	// ������� ����������
	int GetYear();
	int GetAge();
	int GetNumber_of_skills();
	int GetSalary();
	// ������� ������� ������
	int NowAge(int now_year);
	int NowNumber_of_skills(int now_year);
	double NowSalary(int now_year);
	double Time_for_sum(int sum, int now_year);
};