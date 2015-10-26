// Fig. 21.4: list.h
// Template List class definition.
#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;

#include <new>
#include "listnode.h"  // ListNode class definition

template< class NODETYPE >
class List {

public:
   List();      // constructor
   ~List();     // destructor
   void insertAtFront( const NODETYPE & );
   void insertAtBack( const NODETYPE & );
   void insertMiddle(const NODETYPE &, int );
   bool removeMiddle( NODETYPE&, int);
   bool removeFromFront( NODETYPE & );
   bool removeFromBack( NODETYPE & );
   bool isEmpty() const;
   void print() const;
   int counter();

private:
   ListNode< NODETYPE > *firstPtr;  // pointer to first node
   ListNode< NODETYPE > *lastPtr;   // pointer to last node

   // utility function to allocate new node
   ListNode< NODETYPE > *getNewNode( const NODETYPE & );

}; // end class List

// default constructor
template< class NODETYPE >
List< NODETYPE >::List() 
   : firstPtr( 0 ), 
     lastPtr( 0 ) 
{ 
   // empty body

} // end List constructor

// destructor
template< class NODETYPE >
List< NODETYPE >::~List()
{
   if ( !isEmpty() ) {    // List is not empty
//      cout << "Destroying nodes ...\n";

      ListNode< NODETYPE > *currentPtr = firstPtr;
      ListNode< NODETYPE > *tempPtr;

      while ( currentPtr != 0 )         // delete remaining nodes
      {  
         tempPtr = currentPtr;

// commented out the output -- no need to print what we are deallocating
//         cout << tempPtr->data << '\n';  

         currentPtr = currentPtr->nextPtr;
         delete tempPtr;

      }

   }

//   cout << "All nodes destroyed\n\n";

} // end List destructor

// insert node at front of list
template< class NODETYPE >
void List< NODETYPE >::insertAtFront( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      newPtr->nextPtr = firstPtr;
      firstPtr = newPtr;

   } // end else

} // end function insertAtFront

// insert node at back of list
template< class NODETYPE >
void List< NODETYPE >::insertAtBack( const NODETYPE &value )
{
   ListNode< NODETYPE > *newPtr = getNewNode( value );

   if ( isEmpty() )  // List is empty
      firstPtr = lastPtr = newPtr;

   else {  // List is not empty
      lastPtr->nextPtr = newPtr;
      lastPtr = newPtr;

   } // end else

} // end function insertAtBack

// delete node from front of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromFront( NODETYPE &value )
{
   if ( isEmpty() )  // List is empty
      return false;  // delete unsuccessful

   else {  
      ListNode< NODETYPE > *tempPtr = firstPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else
         firstPtr = firstPtr->nextPtr;

      value = tempPtr->data;  // data being removed
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromFront

// delete node from back of list
template< class NODETYPE >
bool List< NODETYPE >::removeFromBack( NODETYPE &value )
{
   if ( isEmpty() )
      return false;  // delete unsuccessful

   else {
      ListNode< NODETYPE > *tempPtr = lastPtr;

      if ( firstPtr == lastPtr )
         firstPtr = lastPtr = 0;
      else {
         ListNode< NODETYPE > *currentPtr = firstPtr;

         // locate second-to-last element
         while ( currentPtr->nextPtr != lastPtr )
            currentPtr = currentPtr->nextPtr;

         lastPtr = currentPtr;
         currentPtr->nextPtr = 0;

      } // end else

      value = tempPtr->data;
      delete tempPtr;

      return true;  // delete successful

   } // end else

} // end function removeFromBack

// is List empty?
template< class NODETYPE > 
bool List< NODETYPE >::isEmpty() const 
{ 
   return firstPtr == 0; 
   
} // end function isEmpty

// return pointer to newly allocated node
template< class NODETYPE >
ListNode< NODETYPE > *List< NODETYPE >::getNewNode( 
   const NODETYPE &value )
{
   return new ListNode< NODETYPE >( value );

} // end function getNewNode

// display contents of List
template< class NODETYPE >
void List< NODETYPE >::print() const
{
   if ( isEmpty() ) {
      cout << "The list is empty\n\n";
      return;

   } // end if

   ListNode< NODETYPE > *currentPtr = firstPtr;

   cout << "The list is: ";

   while ( currentPtr != 0 ) {
      cout << currentPtr->data << ' ';
      currentPtr = currentPtr->nextPtr;

   } // end while

   cout << "\n\n";

} // end function print
template< class NODETYPE >
void List<NODETYPE>::insertMiddle(const NODETYPE & value, int index ){
   //create a new node that holds value inputted
  ListNode< NODETYPE > *newPtr = getNewNode( value );
   //first check to make sure list has content
  if ( isEmpty() )  // List is empty
     firstPtr = lastPtr = newPtr;
   // List is not empty
  else {  
    //set current to first pointer
     ListNode< NODETYPE > *currentPtr = firstPtr;
     //insert at back if index higher than nodes
     if(counter() < index)
        insertAtBack(value);
     else if (index <= 0)
        insertAtFront(value);
	 
     else if(index == 1)
         insertAtFront(value);
     else{
        index--;
		//walkthrough till index reached
        while ( --index != 0)
           currentPtr = currentPtr->nextPtr;
		//have the node after the new node be the current nodes next node
        newPtr->nextPtr = currentPtr->nextPtr;
		//have the node after the current node be the new node
        currentPtr->nextPtr = newPtr;
    }
   } // end else
}
template< class NODETYPE >
bool List< NODETYPE >::removeMiddle( NODETYPE & value, int index){
   if(isEmpty() || counter() < index || index <=0)
      return false;
   else{
      //Current points to head
      ListNode< NODETYPE > *currentPtr = firstPtr;
      
      if(index == 1)
         removeFromFront(value);
	  
      else{
         index--;
         while ( --index !=0)
         //current points to the next node
         currentPtr = currentPtr->nextPtr;
         //store node to be deleted
         ListNode< NODETYPE > *deletedPtr = currentPtr->nextPtr;
         //connect ptr behind the node to be deleted with the next node
         //after the node to be deleted
         currentPtr->nextPtr = currentPtr->nextPtr->nextPtr;
         //delete that node
         //store the to be deleted into value
         value = deletedPtr->data;
         delete deletedPtr;
         return true;
      }
   }
}
template< class NODETYPE >
int  List< NODETYPE >::counter(){
   ListNode< NODETYPE > *countPtr = firstPtr;
   int count = 0;   
   //goes through and adds up each node on the walkthrough
   while ( countPtr != NULL ){
      countPtr = countPtr->nextPtr;
      count++;
   }
   return count;
}

#endif
