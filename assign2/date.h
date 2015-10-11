#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Date
{
public:
	//constucor with default values
	Date(int m = 1, int d = 1, int y = 2000);

	void Input();
	void Show();

	//checks if date is valid
	bool Set(int m, int d, int y);
	
	//accessors
	int GetMonth()const;
	int GetDay()const;
	int GetYear()const;
	
	//will default to default format
	//takes in value from main 
	bool SetFormat(char f);

	//increases date with default of one day
	void Increment(int numDays = 1);

	//compares date objects
	int Compare(const Date& d);
private:
	//member data
	int month;
	int day;
	int year;

	char f;
	char format;
};
