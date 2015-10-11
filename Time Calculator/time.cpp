#include "time.h"
                
Time::Time()
{
   //intializing all values to 0 if no parameters
   days = 0;
   hours = 0;
   minutes = 0;
   seconds = 0;
}
Time::Time(int s)   
{
   //here the default contructor will convert seconds to a time object if one param passed in
   seconds = s;
   //sets time to 0 if negative passed in
   if (seconds < 0){ 
      days = 0;   
      hours = 0;  
      minutes = 0;
      seconds = 0;
   }
   //these are the conversion functions that will check and adjust times
   //so that they are valid
   //if seconds is greater than 59 then this function will have minutes(an int)
   //equal to seconds /60 and then seconds is readjusted to be within 
   //60 by using modulus so 61 seconds becomes 1 minute and 1 second
   if(seconds > 59){
      minutes = seconds / 60;
      seconds = seconds % 60;   
   }
   //the previous process is applied for the following segemnts
   if (minutes > 59){
      hours = minutes / 60;  
      minutes = minutes % 60;
   }
   if (hours > 23){
      days = hours / 24;
      hours = hours % 24;
   }
   //since this is the conversion constructor if the amount of seconds does 
   //not make the hours go over 23, then the days must be zero
   else
      days = 0;
}        
Time::Time(int d, int h, int m, int s)
{
   //this is the constructor with the full set of parameters
   //it begins by declaring all the parameters as the private member data
   days = d;   
   hours = h;
   minutes = m;
   seconds = s;
   //checks to ensure all the member data is positive
   if (seconds < 0 || minutes < 0 || hours < 0 || days < 0){
      days = 0;
      hours = 0;
      minutes = 0;
      seconds = 0;
   }
   //and then goes through the routine we saw previosuly, making sure all the 
   //data is adjusted appropriately
   if(seconds > 59){
      minutes += seconds / 60;
      seconds = seconds % 60;   
   }
   if (minutes > 59){
      hours += minutes / 60;  
      minutes = minutes % 60;
   }
   if (hours > 23){
      days += hours / 24;
      hours = hours % 24;
   }
       
}     
Time verify(Time t)
{
   //verifies correct time using some of the previous calculations from previosuly to
   //ensure data is correct
   //these first three if statements are here for win the amounts exceed the upper limits
   if(t.seconds > 59){
      t.minutes += t.seconds / 60;
      t.seconds = t.seconds % 60;
   }  
   if (t.minutes > 59){
     t.hours += t.minutes / 60;
     t.minutes = t.minutes % 60;
   }
   if (t.hours > 23){
     t.days += t.hours / 24;
     t.hours = t.hours % 24;
   }
   //these three are for when the amounts drop below the lower limits
   if (t.hours < 0){
      t.days--;
	  //creates temp variable so that we come back to our initial hours
	  //after resetting it
      int temp = t.hours;
      t.hours = 23;
	  //adding on because hours is negative
      t.hours += temp;
      t.hours++;
   }
   //same process as the previous if statements
   if (t.minutes < 0){
      t.hours--;
      int temp = t.minutes;  
      t.minutes = 59;
      t.minutes += temp;
      t.minutes++;
   }
   if(t.seconds < 0){
      t.minutes--;
      int temp = t.seconds;
      t.seconds = 59;
      t.seconds += temp;
      t.seconds++;    
   }
   return(t);
}
ostream& operator<< (ostream& os, const Time& t1)
{
   //this function will print out the time function
   //first we verify the param object using the verify friend function, discussed later
   Time t = verify(t1);
   //this verified object now goes through some if/else statements to place zeros in front
   //of the data when needed
   if (t.hours < 10 && t.minutes < 10 && t.seconds < 10)
      os << t.days << "~" << "0" <<  t.hours << ":" << "0" << t.minutes << ":" << "0" << t.seconds;
   else if (t.minutes < 10 && t.seconds < 10)
      os << t.days << "~" <<  t.hours << ":" << "0" << t.minutes << ":" << "0" << t.seconds;
   else if (t.hours < 10 && t.seconds < 10)
      os << t.days << "~" << "0" << t.hours << ":" << t.minutes << ":" << "0" << t.seconds;
   else if (t.hours < 10 && t.minutes < 10)
      os << t.days << "~" << "0" << t.hours << ":" << "0" << t.minutes << ":" << t.seconds;
   else if(t.hours < 10)
      os << t.days << "~" << "0" << t.hours << ":"<< t.minutes << ":" << t.seconds;
   else if(t.minutes < 10)
      os << t.days << "~" << t.hours << ":" << "0" << t.minutes << ":" << t.seconds;
   else if (t.seconds < 10)
      os << t.days << "~" <<  t.hours << ":" << t.minutes << ":" << "0" << t.seconds;
   else
      os << t.days << "~" <<  t.hours << ":" << t.minutes << ":" << t.seconds;
    return os;
}
istream& operator>> (istream& is, Time& t)
{
   //junk character for tilde/colon
   char tilon;
   is >> t.days >> tilon >> t.hours >> tilon >> t.minutes >> tilon >> t.seconds;
   //checks to ensure all input data is positive
   if (t.days < 0 || t.hours < 0 || t.minutes < 0 || t.seconds < 0){
      t.days = 0;
      t.hours = 0;
      t.minutes = 0;
      t.seconds = 0;
   }
   //needs to verify that the data is appropriate
   //verify is probably not needed here, or anywhere
   // else, but afraid changing it now may
   //have unforseen consequences so I will leave it in
   //as it doesn't harm the program 
   verify(t);
   return is;
      
}
Time operator+(const Time& t1, const Time& t2)
{
   //creates time object to mess with param data
   Time t3;
   //goes through and adds all param data making it become the new t3 data
   t3.days = t1.days + t2.days;
   t3.hours = t1.hours + t2.hours;
   t3.minutes = t1.minutes + t2.minutes;
   t3.seconds = t1.seconds + t2.seconds;
   //verifies data is correct
   verify(t3);
   return (t3);
}
Time operator+(const Time& t1, int n)
{
   Time t2;
   //adds the 'n' param to seconds and then adjusts accordingly
   t2.seconds = t1.seconds +  n;
   t2.minutes = t1.minutes;
   t2.hours = t1.hours;
   t2.days = t1.days;
   verify(t2);
   return (t2);
}

Time operator-(const Time& t1, const Time& t2)
{
   Time t3;     
   t3.days = t1.days - t2.days; 
   t3.hours = t1.hours - t2.hours;
   t3.minutes = t1.minutes - t2.minutes;
   t3.seconds = t1.seconds - t2.seconds;
   //checks to ensure non negative data is outputted
   if (t1.days < t2.days){
      t3.days = 0; 
      t3.hours = 0;
      t3.minutes = 0;
      t3.seconds = 0;
   }
   else if(t1.days == t2.days && t1.hours < t2.hours){
      t3.days = 0;   
      t3.hours = 0;  
      t3.minutes = 0;
      t3.seconds = 0;
   }

   else if(t1.days == t2.days && t1.hours == t2.hours && t1.minutes < t2.minutes){
      t3.days = 0;
       t3.hours = 0;
       t3.minutes = 0;
       t3.seconds = 0;
   }
   else if(t1.days == t2.days && t1.hours == t2.hours && t1.minutes == t2.minutes && t1.seconds < t2.seconds){ 
       t3.days = 0;
       t3.hours = 0;
       t3.minutes = 0;
       t3.seconds = 0;
    }

   verify(t3);
   return(t3);

}
Time operator*(const Time& t1, int n)
{
	//function to multiply by in 'n'
   Time t2;
   t2.days = t1.days * n;
   t2.hours = t1.hours * n;
   t2.minutes = t1.minutes * n;
   t2.seconds = t1.seconds * n;
   verify(t2);
   return t2;
}
//comparison operators
bool operator== (const Time& t1, const Time& t2)
{
   if (t1.days == t2.days && t1.hours == t2.hours && t1.minutes == t2.minutes && t1.seconds == t2.seconds)
      return true;
   else 
      return false;
}
bool operator!= (const Time& t1, const Time& t2)
{
   //uses == function call to determine if !=
   if (operator==(t1, t2) == false)
      return true;
   else 
      return false;
}
bool operator< (const Time& t1, const Time& t2)
{
   if (t1.days < t2.days && t1.hours < t2.hours && t1.minutes < t2.minutes && t1.seconds < t2.seconds)
      return true;
   else 
      return false;
}

bool operator> (const Time& t1, const Time& t2)
{
   //uses < function call to determine if >
   if(operator< (t1,t2) == false && t1 != t2)
      return true;
   else 
      return false;
}
bool operator<= (const Time& t1, const Time& t2)
{
   //uses both < and == functions to determine if <=
   if(operator<(t1, t2) == true || operator==(t1,t2) == true)
      return true;
   else 
      return false;
}
bool operator>= (const Time& t1, const Time& t2)
{
   //uses both > and == functions to determine if >=
   if(operator>(t1, t2) == true || operator==(t1,t2) == true)
      return true;
   else 
      return false;
}
//increment and decrement operators
Time Time:: operator++(int)
{
   //here im pretty much following the example in the lecture notes
   //with a little bit of adjusting thrown in to account for going
   //over some of the limits
   Time temp = *this;
   seconds += 1;
   if(seconds > 59){
      minutes += seconds / 60;
      seconds = seconds % 60;   
   }
   if (minutes > 59){
      hours += minutes / 60;  
      minutes = minutes % 60;
   }
   if (hours > 23){
      days += hours / 24;
      hours = hours % 24;
   }
   return temp;
}

Time& Time::operator++()
{
   //this is the preincrement operator
   //follows same standard as previous
   seconds +=1;
   if(seconds > 59){
      minutes += seconds / 60;
      seconds = seconds % 60;   
   }
   if (minutes > 59){
      hours += minutes / 60;  
      minutes = minutes % 60;
   }
   if (hours > 23){
      days += hours / 24;
      hours = hours % 24;
   }
   return *this;
}
Time Time:: operator--(int)
{
   //again following the example in lecture notes with a bit of
   //adjusting thrown in to account for going below certain limits
   Time temp = *this;
   seconds -=1;
   if(seconds < 0){
      //so if seconds happens to be less than zero
      //then decrement minute by one to account for this 
      //and then set seconds to 59
      //this can be hard coded because we are just decreasing by one everytime
      minutes--;
      seconds = 59;   
   }
   //the above pattern is used throughout the next couble steps
   if (minutes <= 0){
      hours--;  
      minutes = 59;
   }
   if (hours < 0){
      days--;
      hours = 23;
   }
   return temp;
}
Time& Time::operator--()
{
   //again following same basic principle from lecture
   //and verification done in the same way
   seconds -= 1;
   if(seconds < 0){
      minutes--;
      seconds = 59;   
   }
   if (minutes <= 0){
      hours--;  
      minutes = 59;
   }
   if (hours < 0){
      days--;
      hours = 23;
   }
   return *this;
}
