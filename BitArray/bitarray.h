//   bitarray.h
//
//   BitArray class declaration

#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <iostream>
using namespace std;

class BitArray
{
   friend ostream& operator<< (ostream& os, const BitArray& a);
   friend bool operator== (const BitArray&, const BitArray&);
   friend bool operator!= (const BitArray&, const BitArray&);

public:
   BitArray(unsigned int n);    // Construct an array that can handle n bits
   BitArray(const BitArray&);   // copy constructor
   ~BitArray();                 // destructor

   BitArray& operator= (const BitArray& a);  // assignment operator

   unsigned int Length() const;            // return number of bits in bitarray

   void Set   (unsigned int index);        // set bit with given index to 1
   void Unset (unsigned int index);        // set bit with given index to 0
   void Flip  (unsigned int index);        // change bit (with given index)
   bool Query (unsigned int index) const;  // return true if the given bit
                  //  is set to 1, false otherwise
 

private:
   unsigned char* barray;         // pointer to the bit array
   int arraySize;
   const static int sizeOfChar = sizeof(unsigned char) * 8; 
   
};

#endif