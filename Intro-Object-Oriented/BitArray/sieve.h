#include <iostream>
#include "bitarray.h"
#include <cmath>

using namespace std;

   void Sieve(BitArray& b){
      //first prime number
      int nextPrime = 2;
      //set bits to 1
      for(int i = 0; i < b.Length(); i++)
         b.Set(i);
      //set 1st and 0th to 0
      b.Unset(0);
      b.Unset(1);
      
      //while the prime number is less than the squareroot, continue(for optimization)
      while(nextPrime  < sqrt(b.Length())){
         //go through each number and check if mulitple of prime number
         //start at prime + 1 cause we already know about next prime being prime
         for(int i = nextPrime + 1; i < b.Length(); i++){
            //if multiple of nextprime then unset
            if(i % nextPrime == 0){
               b.Unset(i);
               
            }
         }
         //if a number is still set to 1 then use that as next prime number and continue
         for(int k = nextPrime + 1; k < b.Length(); k++){

            if(b.Query(k)){
               nextPrime = k;
               //need to break once one is found or else this will just keep running through
               //exhausting all numbers
               break;
            }
         }
      }
      
         
      

      
   
   
   }

   



