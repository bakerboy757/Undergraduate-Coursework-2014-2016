#ifndef stack_H
#define stack_H
#include <iostream>
#include <vector>

namespace cop4530{

   template<typename T>
      class stack{
          public:
             //zero argument constructor
             stack();
             //destructor
             ~stack();    
             //copy constructor
             stack(const stack<T>&);
             //move constructor
             stack(stack<T>&&);
             stack<T>& operator= (const stack <T>&);  
             stack<T> & operator=(stack<T> &&);
             //returns true if the stack contains no elements
             bool empty() const;
             //delete all elements from the stack
             void clear();
             //adds x to the stack copy version
             void push(const T& x);
             //adds x to the stack move version
             void push(const T&& x);
             //removes and discards the most recently added element of the stack
             void pop();
             //mutator that returns a reference to the most recently added element of the stack
             T& top();
             //accessor that returns the most recently added element of the stack
             const T& top() const;
             //returns the number of elements stored in stack
             int size() const;
             //print elements of stack to ostream os
             void print(std::ostream& os, char ofc = ' ') const;   
          private:
              std::vector<T> v;
     
      };
      //overloaded comparison opertors

      // invokes the print() method to print the stack<T> a in the specified ostream    
      template<typename T>
      std::ostream& operator<< (std::ostream& os, const stack<T>& a);
      //returns true if the two compared stacks have the same elements, in the same order.  
      template<typename T>
      bool operator== (const stack<T>& lhs, const stack <T>& rhs);
      // opposite of operator==()
      template<typename T>
      bool operator!=(const stack<T>& lhs, const stack <T>& rhs);

      /*returns true if every element in stack a is smaller than
      corresponding elements of Statck b*/
      template<typename T>
      bool operator<= (const stack<T>& a, const stack <T>& b);

       #include "stack.hpp"

     

}//end of namespace 4530

#endif
