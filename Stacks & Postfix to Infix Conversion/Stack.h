#ifndef STACK_H
#define STACK_H
#include <iostream>

namespace cop4530{

   template<typename T>
      class Stack{
		  //overloaded comparison opertors

		  // invokes the print() method to print the Stack<T> a in the specified ostream    
		  template<typename T>
		  friend std::ostream& operator<< (std::ostream& os, const Stack<T>& a);
		  //returns true if the two compared Stacks have the same elements, in the same order.  
		  template<typename T>
		  friend bool operator== (const Stack<T>&, const Stack <T>&);
		  // opposite of operator==()
		  template<typename T>
		  friend bool operator!=(const Stack<T>&, const Stack <T>&);

		  /*returns true if every element in Stack a is smaller than
		  corresponding elements of Statck b, i.e., if repeatedly invoking top()
		  and pop() on both a and b will generate a sequence of elements a_i
		  from a and b_i from b, and for every i,  a_i = b_i, until a is empty.
		  */
		  template<typename T>
		  friend bool operator<= (const Stack<T>& a, const Stack <T>& b);
	  private:
		  struct Item {
			  T data;
			  Item* prev;
			  Item(const T& d = T{}, Item* p = nullptr)
				  : data{ d }, prev{ p }{}
			  Item(T&& d, Item* p = nullptr)
				  : data{ std::move(d) }, prev{ p }{}
		  };
		  

      public:
         //zero argument constructor
         Stack();
         //destructor
         ~Stack();    
         //copy constructor
         Stack(const Stack<T>&);
         //move constructor
         Stack(Stack<T>&&);
         Stack<T>& operator= (const Stack <T>&);  
         Stack<T> & operator=(Stack<T> &&);
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
	     /*print elements of Stack to ostream os. ofc is the separator 
	     between elements in the stack when they are printed out. Note that 
         print() prints elements in the opposite order of the Stack (that is, the 
         oldest element should be printed first).*/ 
         void print(std::ostream& os, char ofc = ' ') const;   
	  private:
		  Item* stackPtr;
		  int theSize;
	 
	  };

	   #include "Stack.hpp"

	 

}//end of namespace 4530

#endif
