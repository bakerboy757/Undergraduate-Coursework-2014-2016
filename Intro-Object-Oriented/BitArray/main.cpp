#include <iostream>

using namespace std;

#include "sieve.h"
#include "bitarray.h"

int main()
{
   unsigned int i, max, counter = 0;

   cout << "\nEnter a positive integer for the maximum value: ";
   cin >> max;

   BitArray ba(max);
   
   
  
  

   Sieve(ba);                    // find the primes (marking the bits)
   //ba.Flip(0);
   cout << "The bit array looks like this: \n"
        << ba
        << '\n';  
  BitArray ca(max);
  
    cout << "The bit array ca looks like this: \n"
        << ca
        << '\n'; 
   cout << "\nPrimes less than " << max << ':' << '\n';
   for (i = 0; i < max; i++)
   {    
       if (ba.Query(i))
       {
	    counter++;
            cout << i;
            if (counter % 8 == 0)
            {
                cout << '\n';
                counter = 0;
            }
            else
                cout << '\t';
       }
   }

   if (ba == ca)
	   cout << "They are equal" << endl;
   else 
	   cout << "They are not equal" << endl;
   cout << "\nGoodbye!\n";
   return 0;
}
