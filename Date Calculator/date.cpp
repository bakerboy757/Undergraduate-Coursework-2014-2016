#include "date.h"

Date::Date(int m, int d, int y)
{
	// decalring values to be used later in code
	month = m;
	day = d;
	year = y;
	//ensures parametes are valid
	if(Set(m, d, y) == false){
		month = 1;
		day = 1;
		year = 2000;
	}
}
void Date::Input()
{
	char bSlash;// to throw out for user input
	int count = 0;
	do{
		//if the loop repeats, print an error message
		if (count != 0){
			cout << "Invalid date. Try again: ";
			cin >> month >> bSlash >> day >> bSlash >> year;
		}
		cout << "Enter a date: ";
		cin >> month >> bSlash >> day >> bSlash >> year;
		count++;
	} while (Set(month, day, year) == false);
}
void Date::Show()
{	
	// used to store long month format data
	string longMonth;
	int julDay;

	if (SetFormat(format) == true){
		switch (format){
		case 'D':
		case 'd':
			cout << month << "/" << day << "/" << year;
			break;
		case 'T':
		case 't':
			if (month < 10)
				cout << "0" << month;
			else
				cout << month;
			if (day < 10)
				cout << "/0" << day;
			else
				cout << "/" << day;
			if (year >= 1000)
				//cuts off the beginning two numbers of the year
				//setfill used here to add in exra zero when year ends in '00
				cout << "/" <<setw(2) << setfill('0') << year % 100;
			else if (year < 1000 && year >= 100)
				// cuts off just 1 number if between 1000 and 100
				cout << "/" << year % 10;
			break;
		case 'L':
		case 'l':
			//switch statment for determing which month to use
			switch (month){
			case 1:
				longMonth = "Jan";
				break;
			case 2:
				longMonth = "Feb";
				break;
			case 3:
				longMonth = "Mar";
				break;
			case 4:
				longMonth = "Apr";
				break;
			case 5:
				longMonth = "May";
				break;
			case 6:
				longMonth = "June";
				break;
			case 7:
				longMonth = "July";
				break;
			case 8:
				longMonth = "Aug";
				break;
			case 9:
				longMonth = "Sept";
				break;
			case 10:
				longMonth = "Oct";
				break;
			case 11:
				longMonth = "Nov";
				break;
			case 12:
				longMonth = "Dec";
				break;
			}
			cout << longMonth << " " << day << ", " << year << endl;
			break;
		// julian portion
		case 'J':
		case 'j':
			switch (month){
			case 1:
				julDay = day;
				break;
			case 2:
				julDay = day + 31;
				break;
			case 3:
				//each case corresponds to a month and in that month the date is added on to the day
				//but it first checks to see if the year is a leap year
				//this repeats for each step
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 59;
						}
						else
							julDay = day + 60;
					}
				}
				else
					julDay = day + 59;
				break;
			case 4:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 90;
						}
						else
							julDay = day + 91;
					}
				}
				else
					julDay = day + 90;
				break;
			case 5:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 120;
						}
						else
							julDay = day + 121;
					}
				}
				else
					julDay = day + 120;
				break;
			case 6:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 151;
						}
						else
							julDay = day + 152;
					}
				}
				else
					julDay = day + 151;
				break;
			case 7:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 181;
						}
						else
							julDay = day + 182;
					}
				}
				else
					julDay = day + 181;
				break;
			case 8:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 212;
						}
						else
							julDay = day + 213;
					}
				}
				else
					julDay = day + 212;				
				break;
			case 9:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 243;
						}
						else
							julDay = day + 244;
					}
				}
				else
					julDay = day + 243;				
				break;
			case 10:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 273;
						}
						else
							julDay = day + 274;
					}
				}
				else
					julDay = day + 273;				
				break;
			case 11:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 304;
						}
						else
							julDay = day + 305;
					}
				}
				else
					julDay = day + 304;				
				break;
			case 12:
				if (year % 4 == 0){
					if (year % 100 == 0){
						if (year % 400 != 0){
							julDay = day + 334;
						}
						else
							julDay = day + 335;
					}
				}
				else
					julDay = day + 334;				
				break;
			}
			//will always be 1-12 since anything outside
			//is not allowed
			//prints out the appropriate zero when needed
			//pins out julian day
			cout << setw(2) << setfill('0') << year % 100 << "-" << setw(3) << setfill('0') << julDay;
			break;

		//default case of main format switch		
		default:
			cout << month << "/" << day << "/" << year;
		}
	}
	//if format entered is invalid then just put out the default format
	else
		cout << month << "/" << day << "/" << year << endl;

}
bool Date::Set(int m, int d, int y)
{
	//checks to ensure valid dates
	month = m;
	day = d;
	year = y;
	if (month > 12 || month < 1)
		return false;
	else if (day > 31 || day < 1)
		return false;
	//start check for leap yaer
	else if (month == 2 && year % 400 == 0 && day > 29)
		return false;
	else if (month == 2 && year % 100 == 0 && year % 400 != 0 && day > 28)
		return false;
	else if (month == 2 && year % 4 == 0 && day > 29)
		return false;
	else if(month == 2 && year % 4 != 0 && day >28)
		return false;
	//end check for leap year
	else if (month % 2 == 0 && month < 8 && day > 30)
		return false;
	else if (month % 2 == 1 && month >= 8 && day > 30)
		return false;
	else if (year < 0)
		return false;
	//passes checks and is valid:
	else
		return true;

}
int Date::GetMonth() const
{
	return month;
}
int Date::GetDay() const
{
	return day;
}
int Date::GetYear() const
{
	return year;
}
bool Date::SetFormat(char f)
{
	//checks to ensure valid character entered
	switch (f){
	//default
	case 'D':
	case 'd':
		format = f;
		return true;
		break;
	//twodigit
	case 'T':
	case 't':
		format = f;
		return true;
		break;
	//long format
	case 'L':
	case 'l':
		format = f;
		return true;
		break;
	//julian
	case 'J':
	case 'j':
		format = f;
		return true;
		break;
	default:
		return false;
	}
}
void Date::Increment(int numDays)
{
	//check to see if number of days added plus the current date remains in thaT month
	//then just add the two together
	//This portion checks for leap year status
	if (month == 2 && (day + numDays) <= 29 && year % 4 == 0 ){
		if (year % 100 == 0){
			if (year % 400 != 0){
				month = month + 1;
				day = day + numDays - 28;
			}
			else
				day = day + numDays;
		}
		else
			day = day + numDays;
	}
	else if(month == 2 && (day + numDays) <= 28 && year % 4 != 0 )
		day = day + numDays;
	else if (month == 2){
		month = month + 1;
		day = day + numDays - 28;
	}
	//leap year status check ends
	else if ((day + numDays) <= 30 && month % 2 == 0 && month < 8)
		day = day + numDays;
	else if ((day + numDays) <= 31 && month % 2 == 0 && month >= 8)
		day = day + numDays;
	else if ((day + numDays) <= 31 && month % 2 == 1 && month < 8)
		day = day + numDays;
	else if ((day + numDays) <= 30 && month % 2 == 1 && month >8)
		day = day + numDays;
	//if however adding days would result in a month change
	//then do these statements
	else
	{
		//first checks month is not december
		if (month < 12){
			//then don't worry about increasing year just add to the month
			month = month + 1;
			if (month % 2 == 0 && month >= 8)
				day = day + numDays - 30;
			else if (month % 2 == 1 && month > 8)
				day = day + numDays - 31;
			else if (month < 8 && month % 2 == 0){
				if (month == 1)
					day = day + numDays - 28;
				else
					day = day + numDays - 31;
			}
			else if (month < 8 && month % 2 == 1)
				day = day + numDays - 30;
		}
		//if it is december then add 1 to the year if it goes over
		else{
			year = year + 1;
			month = 1;
			day = day + numDays - 31;
		}
	}
}
int Date::Compare(const Date& d)
{
	//these compare the calling object and he parameter
	//0 if equal daes
	//-1 if calling object comes first
	//1 if parameter comes first
	if (d.month == month && d.day == day && d.year == year)
		return 0;
	if (d.month > month && d.day > day && d.year > year)
		return -1;
	if (d.year > year)
		return -1;
	else if(d.month > month && d.year > year)
		return -1;
	else if(d.month >= month && d.day > day && d.year == year)
		return -1;
	else
		return 1;
}



