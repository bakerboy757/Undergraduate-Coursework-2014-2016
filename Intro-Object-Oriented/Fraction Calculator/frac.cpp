//--------------- FRAC.CPP ---------------
// The class definition for fractions.
//
// Bob Myers

#include "frac.h"	// iostream is already included in frac.h

// friend functions (operator overloads)

Fraction operator+(const Fraction& f1, const Fraction& f2)
{
   Fraction r;        // declare a Fraction to hold the result

   // load result Fraction with sum of adjusted numerators
   r.numerator = (f1.numerator*f2.denominator)
                  + (f2.numerator*f1.denominator);

   // load result with the common denominator
   r.denominator = f1.denominator * f2.denominator;
   r.Simplify();
   return r;         // return the result Fraction
}

Fraction operator*(const Fraction& f1, const Fraction& f2){
   //declares a fraction to hold product
   Fraction p;
   //multiplies and stores both numerators and denominators in p;
   p.numerator = f1.numerator * f2.numerator;
   p.denominator = f1.denominator * f2.denominator;
   
   //simplifies product fraction
   p.Simplify();
   //returns product as fraction
   return p;
}
bool operator< (const Fraction& f1, const Fraction& f2)
{
   return (f1.numerator*f2.denominator < f2.numerator*f1.denominator);
}

bool operator> (const Fraction& f1, const Fraction& f2)
{
   return (f2 < f1);
}

bool operator== (const Fraction& f1, const Fraction& f2)
{
   return !(f1 < f2 || f2 < f1);
}

ostream& operator<< (ostream& os, const Fraction& f)
{  
  os << f.numerator << '/' << f.denominator;
  return os;
}





// member functions

Fraction::Fraction()
// Default constructor.  Initializes fraction to 0/1
{
   numerator = 0; 
   denominator = 1;
}

Fraction::Fraction(int n, int d)
// initializes fraction to n/d (defaults to 0/1 if invalid data)
{
   if (SetValue(n, d) == false)
	SetValue(0, 1);
}

void Fraction::Input()
// Get a fraction from standard input, in the form 
//"numerator/denominator."
// what kind of error checking should be added?
{
   char divSign;	// used to consume the '/' character during input
   do
   {
      cin >> numerator >> divSign >> denominator;
      if (denominator <= 0)
	cout << "*** Denominator must be positive.  Try again: ";

   } while (denominator <= 0);
}
void Fraction::Simplify(){
   //create temp variabels because I will be altering numerator and denominator to find gcd   
   int tempNum = numerator;
   int tempDen = denominator;
   //r to hold remainder
   int r; 
   //this while loop will compute the gcd using the Euclid's algoritm learned from discrete I
   //run this loop until denom becomes zero
   while(denominator != 0){
      //have remainder = num mod den(in case of 22/66 r would be 44)
      r = numerator % denominator;
      //have num now = den(in case of 22/66 num would now be 66)
      numerator = denominator;
      //set den = remainder(in case of 22/66 den = 44 so we now have 66/44)
      denominator = r;
      //run loops again, once den = 0 then the "numerator" will now be the greatest common divisor
   }
   int gcd = numerator;
   numerator = tempNum / gcd;
   denominator = tempDen / gcd;
   if(denominator < 0){
      numerator *= -1;
      denominator *= -1;
   }

/*this was initial code, it was clunky, took forever to run, and had a - sign error
  commenting out to show initial thought process and the benefit of using Euclid's algorithm
if(numerator == 0){
      numerator = 0;
      denominator = 1;
   }
   //if both are divisible by eachother(ie 2/4 or 6/12) then
   //then set denom = to the denom / num(4 becomes 2)
   //and divide numerator by itself(2 becomes 1)
   else if(denominator % numerator == 0){
      denominator = denominator / numerator;
      numerator = numerator / numerator;
   }
   //if the num and denom are not divisible by eachother but have a greatest common divisor
   else if(denominator % numerator != 0){
      //if either is negative
      if(denominator*numerator < 0){
         //i would start at -300 for -10 / 30 and then count up
         for(int i = denominator*numerator; i < -1; i++){
            //once 
	    if((denominator % i == 0)&&(numerator % i == 0)){
	       numerator = numerator / i;
	       denominator = denominator / i;
	       if(denominator < 0){
                  denominator *= -1;
	          numerator *=-1;
	       }
	    }
	}
     }
    else{
       for(int i = denominator*numerator; i > 1; i--){
          if((denominator % i == 0)&&(numerator % i == 0)){
	     numerator = numerator / i;
	     denominator = denominator / i;
          }//end if
       }//end for
    }//end else

      //denominator = denominator / (denominator % numerator);
     // numerator = numerator / (denominator % numerator);
   }//end else if
   //if unable to simplify then dont
   else{
	   numerator = numerator;
	   denominator = denominator;
   }*/
}
/* Commented out, because we're using operator<< now
 void Fraction::Show() const
 // Display a fraction, in the form "numerator/denominator."
 {
    cout << numerator << '/' << denominator;
 }
*/

int Fraction::GetNumerator() const
{
   return numerator;
}

int Fraction::GetDenominator() const
{
   return denominator;
}

bool Fraction::SetValue(int n, int d)
// sets fraction to n/d and returns true for success (good data)
// returns false and leaves fraction alone if bad data
{
   if (d <= 0)
	return false;

   numerator = n;
   denominator = d;
   return true;
}


double Fraction::Evaluate() const
// Calculates and returns the decimal value of a fraction
{
   return static_cast<double>(numerator) / denominator;
}

