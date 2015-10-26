#include "frac.h"
class flist
{
//operator overload for output
friend ostream& operator<<(ostream& os, const flist& a1);

public:
   flist();                               //constructor that initializes size and array
   
   bool Insert(Fraction f1);              //inserts fraction at end of array if room
   bool Insert(Fraction f1, int n);       //inserts fraction at nth position moving everything over
   bool Delete(int n);                    //deletes nth postion and moves everything over

   int Size() const;                      //basically getsize() returns the current size of the array

   Fraction Sum() const;                  //adds up array and returns fraction
   Fraction Product(int f, int l) const;  //multiplies from fth element to lth element
   double Average() const;                //computes the average
   Fraction Largest() const;              //finds max value
   int HowMany(Fraction f1) const;        //how many of user defined fraction appear

   void SimplifyAll();             
   void Clear();
   //void Rotate(int r);

private:
   int startSize;
   Fraction fraction[20];
   int currentSize;

};
