#include "stack.h"

//zero argument constructor
template<typename T>
stack<T>::stack() {
    

}
//destructor
template<typename T>
stack<T>::~stack(){
    v.clear();

}    
//copy constructor
template<typename T>
stack<T>::stack(const stack<T>& rhs){
    v = rhs.v;
}
//move constructor
template<typename T>
stack<T>::stack(stack<T>&& rhs) {
    v = rhs.v;
    rhs.v.clear();
}
template<typename T>
stack<T>& stack<T>::operator= (const stack <T>& rhs){
    stack copy = rhs;
    std::swap(*this, copy);
    return *this;

}  
template<typename T>
stack<T>& stack<T>::operator=(stack<T> && rhs){
    std::swap(v, rhs.v);

    return *this;

}
//returns true if the stack contains no elements
template<typename T>
bool stack<T>::empty() const{
    return v.size() == 0;

}
//delete all elements from the stack
template<typename T>
void stack<T>::clear(){
    while (!empty())
        pop();


}
//adds x to the stack copy version
template<typename T>
void stack<T>::push(const T& x){
    v.push_back(x);

}
//adds x to the stack move version
template<typename T>         
void stack<T>::push(const T&& x){
    v.push_back(std::move(x));
    
}
//removes and discards the most recently added element of the stack
template<typename T>
void stack<T>::pop(){
    v.pop_back();
}
//mutator that returns a reference to the most recently added element of the stack
template<typename T>
T& stack<T>::top(){
    return v[v.size() - 1];

}
//accessor that returns the most recently added element of the stack
template<typename T>
const T& stack<T>::top() const{
    return v[v.size() - 1];

}
//returns the number of elements stored in stack
template<typename T>         
int stack<T>::size() const{
    return v.size();

}
/*print elements of stack to ostream os. ofc is the separator 
between elements in the stack when they are printed out. Note that 
print() prints elements in the opposite order of the stack (that is, the 
oldest element should be printed first).*/ 
template<typename T>
void stack<T>::print(std::ostream& os, char ofc) const{

    for (unsigned int i = 0; i < v.size(); i++) {
        os << v[i] << ofc;
    }


}


//overloaded comparison opertors

// invokes the print() method to print the stack<T> a in the specified ostream    
template<typename T>
std::ostream & operator<<(std::ostream & os, const stack<T>& a)
{
    a.print(os);
    return os;

}

//returns true if the two compared stacks have the same elements, in the same order.  
template<typename T>
bool operator==(const stack<T>& lhs, const stack<T>& rhs)
{
    stack<T> copy_lhs = lhs;
    stack<T> copy_rhs = rhs;
    if (copy_lhs.size() != copy_rhs.size()) return false;
    while (!copy_lhs.empty()) {
        if (copy_lhs.top() != copy_rhs.top())
            return false;
        copy_lhs.pop();
        copy_rhs.pop();
    }
    return true;

}
// opposite of operator==()
template<typename T>
bool operator!=(const stack<T>& lhs, const stack<T>& rhs)
{
    return !(lhs == rhs);

}
/*returns true if every element in stack a is smaller than 
  corresponding elements of Statck b, i.e., if repeatedly invoking top() 
  and pop() on both a and b will generate a sequence of elements a_i 
  from a and b_i from b, and for every i,  a_i = b_i, until a is empty.  
*/
template<typename T>
bool operator<=(const stack<T>& a, const stack<T>& b)
{
    stack<T> copy_a = a;
    stack<T> copy_b = b;
    while (!copy_a.empty()) {
        if (copy_a.top() != copy_b.top()) {
            if (copy_a.top() > copy_b.top())
                return false;
        }
        copy_a.pop();
        copy_b.pop();
        
    }
    return true;

}









