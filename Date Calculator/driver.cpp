/////////////////////////////////////////////////////////
// Bob Myers
//
// sample.cpp -- sample test program starter for Date class
/////////////////////////////////////////////////////////

#include <iostream>
#include "date.h"

using namespace std;

int main()
{
	Date d1(12, 25, 2003);  // should default to 1/1/2000
	Date d2(12, 25, 2003);  // should init to 4/10/1992

	// display dates to the screen
	cout << "\nDate d1 is: ";
	d1.Show();
	cout << "\nDate d2 is: ";
	d2.Show();

	d1.Input();			// Allow user to enter a date for d1
	cout << "\nDate d1 is: ";
	d1.Show();

	d1.SetFormat('T');		// change format of d1 to "Long" format
	cout << "\nDate d1 t is: ";
	d1.Show();			// print d1 -- should show now in long format

	// and so on.  Add your own tests to fully test the class' 
	//   functionality.

	d1.SetFormat('D');		// change format of d1 to "Long" format
	cout << "\nDate d1 default is: ";
	d1.Show();	

	d1.SetFormat('L');		// change format of d1 to "Long" format
	cout << "\nDate d1 long is: ";
	d1.Show();	

	d2.SetFormat('J');
	cout << "\nDate 2 is : ";
	d2.Show();

	d1.Increment();
	cout << "\nDate d1 is now + 1: ";
	d1.Show();	

	d2.Increment();
	cout << "\nDate d2 is now + 5: ";
	d2.Show();

	cout <<"\nd1.Compare(d2)" << d1.Compare(d2) << endl;
        cout <<"\nd2.Compare(d1)" << d2.Compare(d1) << endl;

}
