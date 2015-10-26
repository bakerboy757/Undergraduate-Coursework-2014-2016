
// Sample main program to test the Time class
// Author:  Bob Myers

#include <iostream>
#include "time.h"

using namespace std;

int main()
{
   Time t1, t2, t3(123456), t4(987654321);
   t1 =4321;
   cout << "t1 = " << t1 << '\n';
   cout << "t2 = " << t2 << '\n';
   cout << "t3 = " << t3 << '\n';
   cout << "t4 = " << t4 << '\n';

   cout << "Enter first Time object (DAYS~HH:MM:SS):  ";
   cin >> t1;

   cout << "Enter second Time object (DAYS~HH:MM:SS):  ";
   cin >> t2;

   cout << "t1: " << t1 << endl;
   cout << "t2: " << t2 << endl;
      
   cout << "\n\n"; 
   cout << t1 << " + " << t2 << " = " << t1 + t2 << '\n';
   cout << t1 << " - " << t2 << " = " << t1 - t2 << "\n\n";

   if (t1 < t2)    cout << t1 << " <  " << t2 << " is TRUE\n";
   if (t1 > t2)    cout << t1 << " >  " << t2 << " is TRUE\n";
   if (t1 <= t2)    cout << t1 << " <= " << t2 << " is TRUE\n";
   if (t1 >= t2)    cout << t1 << " >= " << t2 << " is TRUE\n";
   if (t1 == t2)    cout << t1 << " == " << t2 << " is TRUE\n";
   if (t1 != t2)    cout << t1 << " != " << t2 << " is TRUE\n\n";

   cout << t1 << " + 654321 = " << t1 + 654321 << '\n';
   cout << t2 << " + 15263748 = " << t2 + 15263748 << '\n';
   cout << t1 << " * 4 = " << t1 * 4 << "\n\n";
   cout << t1 <<"++t1 = " << ++t1<<"\n\n";
   cout << t2 << "--t2 = "<< --t2 << "\n\n";
   cout << t1 <<"t1++ = " << t1++ <<"\n\n";
   cout << t2 << "t2-- = "<< t2-- << "\n\n";

   cout << t1 << endl;

}
