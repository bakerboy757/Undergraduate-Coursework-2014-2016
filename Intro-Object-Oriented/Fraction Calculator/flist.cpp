#include "flist.h"

ostream& operator<<(ostream& os, const flist& a1){
   //if the size of the array is 0 than it is empty
   if(a1.currentSize == 0)
	   os << "FList is empty" << endl;
   //output up to the current size of the array - 2 index wise
   else{
      for (int i = 0; i < a1.currentSize - 1; i ++)
         os << a1.fraction[i] << ", ";
      //outside the for loop to not have leading comma at end of output
      os << a1.fraction[a1.currentSize - 1] << endl;
   }
   return os;
}
flist::flist(){
   //sets the size of the array to 0 and intializes and declares a new fraction array
   currentSize = 0;
   //Fraction *fraction = new Fraction[currentSize];
   cout << "Creating FList Object" << endl;

}

bool flist::Insert(Fraction f1){
   //inserts f1 at end of array as long as the array has space
   if(currentSize < 20){
      fraction[currentSize] = f1;
      //increases the size
      currentSize++;
      return true;
   }
   else
      return false;
}
bool flist::Insert(Fraction f1, int n){
   //checks to make sure valid position
   if (currentSize < 20 && n > 0 && n < currentSize){
      //puts in dummy to hold onto end of array value (kept getting set to 0/1 without)
      Fraction tempEnd = fraction[currentSize-1];
      //sets dummy for nth position fraction as it kept getting lost
      Fraction tempn = fraction[n-1];
      //goes through and moves everything over to make room for new fraction
      for(int i = currentSize - 1; i > n; --i)
         fraction[i] = fraction[i-1];
      //puts the removed variables back into their right spot
      fraction[n] = tempn;
      fraction[n-1] = f1;
      currentSize++;
      fraction[currentSize - 1] = tempEnd;
      return true;
   }
   else if(currentSize >= 20){
	   cout <<"*** FList full." << endl;
	   return false;
   }
   else{
      cout << "*** Invalid list position" << endl;
      return false;
   }
}

bool flist::Delete(int n){
   //if valid n:
   // moves everything over and decreases size of array
   if(n != 0 && n < currentSize){
      for(int i = n-1; i < currentSize; i++)
         fraction[i]= fraction[i+1];
      currentSize--;
      return true;
   }
   else{
      cout << "*** Invalid position" << endl;
      return false;
   }
}
int flist::Size() const{
   return currentSize;
}
Fraction flist::Sum() const{
   //initializes r
   //then adds all arrays onto r
   Fraction r = fraction[0];
   for(int i = 1; i < currentSize; i++){
      r = r + fraction[i];
   }
   //simplifies before returning
   r.Simplify();
   return r;
}
double flist::Average() const{
   Fraction a = fraction[0];
   for (int i = 1; i < currentSize; i++)
	   a = a + fraction[i];
   //need to static cast to avoid int/int = int scenario
   double b = (static_cast<double>(a.GetNumerator())/a.GetDenominator());
   double average = b / currentSize;
   return average;
}
Fraction flist::Product(int f, int l) const{
   Fraction p = fraction[f-1];
   for(int i = f; i < l; i++){
      p = p * fraction[i];
   }
   return p;
}
Fraction flist::Largest() const{
   Fraction max = fraction[0];
   for(int i = 1;i < currentSize; i++){
      if(max < fraction[i])
         max = fraction[i];
   }
   return max;
}
int flist::HowMany(Fraction f1) const{
   int count = 0;
   for(int i = 0; i < currentSize; i++){
      if( f1 == fraction[i])
         count++;
   }
   return count;
}
void flist::SimplifyAll(){
   for(int i = 0;i < currentSize; i++)
      fraction[i].Simplify();
}
void flist::Clear(){
   //empties the array
   currentSize = 0;
}
/*
void flist::Rotate(int r){
   if(r < 0){
      r = r * -1;
      for (int i = currentSize; i = 0; i--){
         temp
         fraction[i] = fraction[i-r];
      }
   }
   else if (r > 0){
      for(int i = r; i =0;i++)
         fraction[i] = fraction[i-1];
   }
   
}*/
