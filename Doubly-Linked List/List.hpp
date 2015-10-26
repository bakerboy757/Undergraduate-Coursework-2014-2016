#include "List.h"

//nested const_iterator class:
// default zero parameter constructor
template<typename T>
List<T>::const_iterator::const_iterator():current{nullptr}
{
    
}

// operator*() to return element
template<typename T>
const T& List<T>::const_iterator::operator*() const
{
    return retrieve();
}
// increment/decrement operators
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this);
    return old;

}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    current = current->prev;
    return *this;

}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --(*this);
    return old;

}

// comparison operators
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator & rhs) const
{
    return current == rhs.current;
}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator & rhs) const
{
    return !(*this == rhs);
}


//Protected: (part of const iter)
//Node *current; // pointer to node in List

// retrieve the element refers to
template<typename T>
T& List<T>::const_iterator::retrieve() const
{
    return current->data;
}
// protected constructor
template<typename T>
List<T>::const_iterator::const_iterator(Node * p) :current{ p }
{
    
}
/******************
*
*  iterator class following
*
*
***************/
    

// nested iterator class:
//class iterator : public const_iterator 
template<typename T>
List<T>::iterator::iterator()
{

}
template<typename T>
T& List<T>::iterator::operator*()
{
    return const_iterator::retrieve();
}
template<typename T>
const T& List<T>::iterator::operator*() const
{
    return const_iterator::operator*();
}

// increment/decrement operators
template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;

}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;

}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;

}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;

}

//protected:
template<typename T>
List<T>::iterator::iterator(Node * p):const_iterator{ p }
{
    

}
/*************
*
*
*    LIST class folllowing
*
*
**************/

//public:
// constructor, desctructor, copy constructor
// default zero parameter constructor
template<typename T>
List<T>::List()
{
    init();
}
// copy constructor
template<typename T>
List<T>::List(const List & rhs)
{
    init();
    for (auto & x : rhs)
        push_back(x);

}
// move constructor
template<typename T>
List<T>::List(List && rhs)
    : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}


// num elements with value of val
template<typename T>
List<T>::List(int num, const T & val)
{	
	//initialize our empty lst
    init();
    int i = 0;
	//while not exceeding num, continue stacking val into the list
    while (i < num) {
        push_front(val);
        i++;
    }
}
// constructs with elements [start, end) from another list
template<typename T>
List<T>::List(const_iterator start, const_iterator end)
{
	//initialize our new list
    init();
	//as we iterate over the passed in List from value
	//start to end, we want to tack on the values to our new
	//List created with init()
    for (const_iterator itr = start; itr != end; itr++) 
        push_back(*itr);
    
}
// destructor
template<typename T>
List<T>::~List()
{
    clear();
    delete head;
    delete tail;

}

 // copy assignment operator
template<typename T>
const List<T>& List<T>::operator=(const List & rhs)
{
    List copy = rhs;
    std::swap(*this, copy);
    return *this;
}
// move assignment operator
template<typename T>
List<T>& List<T>::operator=(List && rhs)
{
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);

    return *this;
}

// member functions:
// number of elements
template<typename T>
int List<T>::size() const
{
    return theSize;
}
// check if list is empty
template<typename T>
bool List<T>::empty() const
{
    return size() == 0;
}
// delete all elements
template<typename T>
void List<T>::clear()
{
    while (!empty())
        pop_front();
}
// reverse the order of the elements
template<typename T>
void List<T>::reverse()
{
    //some code revised from https://www.youtube.com/watch?v=sYcOK51hl-A
    
    for (Node* temp = head; temp != nullptr; temp = temp->prev) {
        std::swap(temp->next, temp->prev);
    }
    std::swap(head, tail);
	//initial thought process
	//head->next = head->prev;
	//head->prev = nullptr;
	//head->next->next = head->next->prev;
	//head->next->next->next = head->next->next->prev;
	//head->next->next->next->next = head->next->next->next->prev;
	//tail->next = nullptr;

}
// reference to the first element
template<typename T>
T& List<T>::front()
{
    return *begin();
}
template<typename T>
const T& List<T>::front() const
{
    return *begin();
}

// reference to the last element
template<typename T>
 T& List<T>::back()
{
    return *--end();
}

template<typename T>
const T & List<T>::back() const
{
    return *--end();
}
// insert to the beginning
template<typename T>
void List<T>::push_front(const T & val)
{
    insert(begin(), val);
    
}
// move version of insert
template<typename T>
void List<T>::push_front(T && val)
{
    insert(begin(), std::move(val));
}
// insert to the end
template<typename T>
void List<T>::push_back(const T & val)
{
    insert(end(), val);

}
// move version of insert
template<typename T>
void List<T>::push_back(T && val)
{
    insert(end(), std::move(val));

}
// delete first element
template<typename T>
void List<T>::pop_front()
{
    erase(begin());

}
// delete last element
template<typename T>
void List<T>::pop_back()
{
    erase(--end());

}
// remove all elements with value = val
template<typename T>
void List<T>::remove(const T & val)
{
    //create an iterator to start at head of our List
    iterator itr(head);
    int i = 0;
	//nested while loops may be uneccessary but errors occur
	//without main while loop
    while (i < theSize) {
		//reset iterator(otherwise crashes)
        iterator itr(head->next);
		//continue through iterator until you find a match, then erase that node
        while (itr != end()) {
            if (*itr == val) {
                erase(itr);
                break;
            }
            itr++;
        }
        i++;
    }

}

// print out all elements. ofc is deliminitor
template<typename T>
void List<T>::print(std::ostream & os, char ofc) const
{
	//start iterator at 1st node that is not head
    iterator itr(head->next);
	//iterate over List, prtinting out the reference
    while (itr != end()) {
        os << *itr;
		os << ofc;
        itr++;
    }

}

// iterator to first element
template<typename T>
typename List<T>::iterator List<T>::begin()
{
    return iterator(head->next);
}
template<typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return const_iterator(head->next);
}
// end marker iterator
template<typename T>
typename List<T>::iterator List<T>::end()
{
    return iterator(tail);
}
template<typename T>
typename List<T>::const_iterator List<T>::end() const
{
    return const_iterator(tail);
}
// insert val ahead of itr
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T & val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{ val, p->prev, p });

}
// move version of insert
template<typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{ std::move(val), p->prev, p });


}
// erase one element
template<typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}
// erase [start, end)
template<typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
    for (iterator itr = start; itr != end;)
        itr = erase(itr);
    return end;
}



//private:
//int theSize; // number of elements
//Node *head; // head node
//Node *tail; // tail node
// initialization(private)
template<typename T>
void List<T>::init()
{
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}


// overloading comparison operators
template<typename T>
bool operator==(const List<T>& lhs, const List<T>& rhs)
{
	//immediately return false if not same size
    if (lhs.size() != rhs.size())
        return false;
	//create two new iterators for each list passed in
    auto lhsitr = lhs.begin(); 
    auto rhsitr = rhs.begin();
	//iterate over LIst until either no match or all matches
    while (lhsitr != lhs.end()) {
        if (*lhsitr != *rhsitr)
            return false;
        lhsitr++;
        rhsitr++;
    }
    
    return true;
}

template<typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs)
{
    return (!(lhs==rhs));
}
// overloading output operator
template<typename T>
std::ostream& operator<<(std::ostream & os, const List<T>& l)
{
    l.print(os);
    return os;
}
            
