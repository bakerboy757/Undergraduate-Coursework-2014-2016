#include <iostream>

using namespace std;

class Time
{
//overloaded operators
//insertion/ extertion operators
friend ostream& operator<< (ostream& s,const Time& t);// print time objects
friend istream& operator>> (istream& s, Time& t);//inputs time objects, does error checking, formats

//arithmetic operators
friend Time operator+ (const Time& t1,const Time& t2); // adds two objects
friend Time operator+ (const Time& t1,int n);
friend Time operator- (const Time& t1, const Time& t2);//subtracts two objects, returns 0 time instead of negative time
friend Time operator* (const Time& t1, int n); // allow time to be multiplied by int

//comparison operators
friend bool operator== (const Time& t1, const Time& t2);
friend bool operator!= (const Time& t1, const Time& t2);
friend bool operator< (const Time& t1, const Time& t2);
friend bool operator> (const Time& t1, const Time& t2);
friend bool operator<= (const Time& t1, const Time& t2);
friend bool operator>= (const Time& t1, const Time& t2);

//verify friend function that will check and adjust values as needed
friend Time verify(Time t1);

public:
   //constructors
   Time(); //default constructor which will initialize object to 0
   Time(int s); // conversion constructor from seconds into to Time object
   Time(int d, int h, int m, int s); // constructor with parameters that set to default or simplify $

   //prefix
   Time& operator++();
   Time& operator--();

   //postfix
   Time operator++(int);
   Time operator--(int);

private:
   //member data
   int days,
       hours,
       minutes,
       seconds;

};
