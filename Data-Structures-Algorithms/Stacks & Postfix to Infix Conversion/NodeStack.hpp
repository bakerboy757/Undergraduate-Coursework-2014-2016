#include "Stack.h"

//zero argument constructor
template<typename T>
Stack<T>::Stack() :stackPtr{nullptr} {
	

}
//destructor
template<typename T>
Stack<T>::~Stack(){
	clear();
	delete stackPtr;

}    
//copy constructor
template<typename T>
Stack<T>::Stack(const Stack<T>& rhs){
	theSize = 0;
	stackPtr = new Item;
	Item * p = rhs.stackPtr;
	Stack temp;
	while (p->prev != nullptr) {
		temp.push(p->data);
		p = p->prev;
	}
	p = temp.stackPtr;
	while (p != nullptr) {
		push(p->data);
		p = p->prev;
	}

}
//move constructor
template<typename T>
Stack<T>::Stack(Stack<T>&& rhs) : theSize{ rhs.theSize }, stackPtr{rhs.stackPtr} {
	rhs.theSize = 0;
	rhs.stackPtr = nullptr;


}
template<typename T>
Stack<T>& Stack<T>::operator= (const Stack <T>& rhs){
	Stack copy = rhs;
	std::swap(*this, copy);
	return *this;


}  
template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && rhs){
	std::swap(theSize, rhs.theSize);
	std::swap(stackPtr, rhs.stackPtr);

	return *this;

}
//returns true if the stack contains no elements
template<typename T>
bool Stack<T>::empty() const{
	return size() == 0;

}
//delete all elements from the stack
template<typename T>
void Stack<T>::clear(){
	while (!empty())
		pop();


}
//adds x to the stack copy version
template<typename T>
void Stack<T>::push(const T& x){
	Item* p = stackPtr;
	++theSize;
	stackPtr = new Item{ x };
	stackPtr->prev = p;

}
//adds x to the stack move version
template<typename T>         
void Stack<T>::push(const T&& x){
	Item* p = stackPtr;
	++theSize;
	stackPtr = new Item{ std::move(x) };
	stackPtr->prev = p;
	
}
//removes and discards the most recently added element of the stack
template<typename T>
void Stack<T>::pop(){
	Item* p = stackPtr;
	stackPtr = p->prev;
	delete p;
	--theSize;

}
//mutator that returns a reference to the most recently added element of the stack
template<typename T>
T& Stack<T>::top(){
	return stackPtr->data;

}
//accessor that returns the most recently added element of the stack
template<typename T>
const T& Stack<T>::top() const{
	return stackPtr->data;

}
//returns the number of elements stored in stack
template<typename T>         
int Stack<T>::size() const{
	return theSize;

}
/*print elements of Stack to ostream os. ofc is the separator 
between elements in the stack when they are printed out. Note that 
print() prints elements in the opposite order of the Stack (that is, the 
oldest element should be printed first).*/ 
template<typename T>
void Stack<T>::print(std::ostream& os, char ofc = ' ') const{
	//gonna put stack into another stack by counting down stack
	Item * p = stackPtr;
	Stack temp;
	while (p != nullptr) {
		temp.push(p->data);
		p = p->prev;
	}
	//then I'm going to count down stack which is basically counting up opriginal stack
	p = temp.stackPtr;
	while (p != nullptr) {
		os << p->data << ofc;
		p = p->prev;
	}


}


//overloaded comparison opertors

// invokes the print() method to print the Stack<T> a in the specified ostream    
template<typename T>
std::ostream & cop4530::operator<<(std::ostream & os, const Stack<T>& a)
{
	a.print(os);
	return os;

}

//returns true if the two compared Stacks have the same elements, in the same order.  
template<typename T>
bool cop4530::operator==(const Stack<T>& lhs, const Stack<T>& rhs)
{
	if (lhs.size() != rhs.size()) return false;
	auto lhs_p = lhs.stackPtr;
	auto rhs_p = rhs.stackPtr;
	while (lhs_p->prev != nullptr) {
		if (lhs_p->data != rhs_p->data) return false;
		lhs_p = lhs_p->prev;
		rhs_p = rhs_p->prev;
	}
	return true;

}
// opposite of operator==()
template<typename T>
bool cop4530::operator!=(const Stack<T>& lhs, const Stack<T>& rhs)
{
	return !(lhs == rhs);

}
/*returns true if every element in Stack a is smaller than 
  corresponding elements of Statck b, i.e., if repeatedly invoking top() 
  and pop() on both a and b will generate a sequence of elements a_i 
  from a and b_i from b, and for every i,  a_i = b_i, until a is empty.  
*/
template<typename T>
bool cop4530::operator<=(const Stack<T>& a, const Stack<T>& b)
{
	if (a == b)
		return true;
	//need to check and see what is required for when a and b are not of same size
	auto a_p = a.stackPtr;
	auto b_p = b.stackPtr;
	while (a_p->prev != nullptr && b_p->prev != nullptr) {
		if (a_p->data > b_p->data) return false;
		a_p = a_p->prev;
		b_p = b_p->prev;
	}
	return true;

}









