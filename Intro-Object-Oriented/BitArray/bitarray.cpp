#include "bitarray.h"




ostream& operator<< (ostream& os, const BitArray& a){
   os << "(";
   //first for loop runs though how many bytes 
   //second runs through how many bits in that byte
   //(counts down for the way computers reads the bits)
   for(int i = 0; i < a.arraySize; i++){
      for(int j = a.sizeOfChar - 1; j >= 0; j--){
         //prints out a 1 or 0 based off this bitwise operation
         //this goes to that array byte and then shifts it right
         //j(bit) places and then using the bit wise and operation
         //with 1 to see if that spot is a 1 or 0
         os << ((a.barray[i] >> j) & 1 ? '1' : '0');
      }
   }
   
   os << ")";
   return os;
}
bool operator== (const BitArray& a, const BitArray& b){

   if(a.arraySize == b.arraySize){
      for(int i = 0; i < a.arraySize; i++){
         if(a.barray[i] != b.barray[i])
            return false;
      }
      return true;
   }
   else 
      return false;
}
bool operator!= (const BitArray& a, const BitArray& b){
   if ((a == b) == false)
      return true;
   else 
      return false;

}

// Construct an array that can handle n bits
BitArray::BitArray(unsigned int n){
   double d = n /sizeOfChar;
   //i will be size of array in char
   arraySize = d;
   //if not divisible by 8 then tack on an extra byte
   if((n % 8) != 0)
      arraySize++;
   
   barray = new unsigned char[arraySize];
   //set all bits to 0
   for(int i = 0; i < arraySize; i ++)
      barray[i] = 0;

}    
// copy constructor
BitArray::BitArray(const BitArray& a){
   arraySize = a.arraySize;
   barray = new unsigned char[a.arraySize];
   for(int i = 0; i < arraySize; i++)
      barray[i] = a.barray[i];
}  
// destructor
BitArray::~BitArray(){
   delete [] barray;
}   
// assignment operator
BitArray& BitArray::operator= (const BitArray& a){
   //same process as on Bob's website
   if(this != &a){

      delete [] barray;
      arraySize = a.arraySize;
      barray = new unsigned char[arraySize];
      for(int i = 0; i < arraySize; i++)
         barray[i] = a.barray[i];
   }
   return *this;
}  
// return number of bits in bitarray
unsigned int BitArray:: Length() const{
   return (arraySize * sizeOfChar);
}            

 // set bit with given index to 1
void BitArray::Set   (unsigned int index){
   //location to see which byte to deal with
   int location = index / sizeOfChar;
   //position to see which bit to deal with(must count back wards
   //hence the sizeOfChar - 1 - )
   int position = sizeOfChar - 1 - (index % sizeOfChar);
   //mask that shifts 1 left position bits
   char mask = (1 << position);
   //bitwise or with mask to set that one bit to 1
   barray[location] = barray[location] | mask;
   
} 
// set bit with given index to 0
void BitArray::Unset (unsigned int index){
   int location = index / sizeOfChar;
   int position = sizeOfChar - 1 -(index % sizeOfChar);
    char mask = 1 << position;
   //as seen in bitflags example
   barray[location] = barray[location] & ~mask;

}     
// change bit (with given index)
void BitArray::Flip  (unsigned int index){
   int location = index / sizeOfChar;
   int position = sizeOfChar - 1 -(index % sizeOfChar);
   char mask = (1 << position);
   //as seen in bitflags example
   barray[location] = barray[location] ^ mask;
}      
// return true if the given bit
//  is set to 1, false otherwise
bool BitArray::Query (unsigned int index) const{
   int location = index / sizeOfChar;
   int position = sizeOfChar - 1 -(index % sizeOfChar);
   char mask = 1 << position;
   //if that bit is a 1(true) return true
   if(barray[location] & mask)
      return true;
   else 
      return false;
   
}  
