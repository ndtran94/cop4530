
#include <iostream>
#include <fstream>
/****************** C O N S T R U C T O R S ************************/
// DEFAULT CONSTRUCTOR
// Pre-Condition:
// Post-Condition: Create empty queue. only consist of head, tail node markers
template <typename T>
Queue<T>::Queue()
{
  head = new Queue::Node();
  tail = new Queue::Node();
  head->next = tail;
  tail->next = nullptr;
  //  tail->prev = head;
  nel = 0;
}
// COPY CONSTRUCTOR
// Pre-Condition: reference Queue object to copy
// Post-Condition: a copy of rhs Queue constructed 
//////////////////////////////
template <typename T>
Queue<T>::Queue( const Queue& rhs ) 
{
  head = new Queue::Node();
  tail = new Queue::Node();
  head->next = tail;
  tail->next = nullptr;
  nel = 0;
  // Queue() not working for creation of head and tail
  //std::cout << "NEL: " << **rhs->nel << std::endl;
  if( !rhs.empty() )
    {
      push( rhs.front() );
      Queue::nodePtr rhsPtr = rhs.head->next->next; 
      while( rhsPtr != rhs.tail )
	{
	  push( rhsPtr->data );
	  rhsPtr = rhsPtr->next;
	}  
    }// end of if
}
// COPY ASSIGNMENT
// Pre-Condition: reference to Queue to copy
// Post-Condition: reassign already created queue to originial
///////////////////////////////////////////////
template <typename T>
const typename Queue<T>:: Queue& Queue<T>::operator=( const Queue& rhs )
{
  //  std::cout << "IN QUEUE COPY ASSIGNMENT" << std::endl;
  if( this != & rhs )
    {
      while( !empty() )
	{
	  pop();
	}
      Queue::nodePtr rhsPtr = rhs.head->next;
      while( rhsPtr != rhs.tail )
	{
	  push( rhsPtr->data );
	  rhsPtr = rhsPtr->next;
	} // end while
    } // end if
  return *this;
} 
// MOVE CONSTRUCTOR
// Pre-Condition:
// Post-COndition: Create a new Queue with the existing elements in rhs 
////////////////////////////////////
template <typename T>
Queue<T>::Queue( Queue&& rhs )
{
  nel = 0;
  head = new Queue::Node();
  tail = new Queue::Node();
  head->next = tail;
  tail->next = nullptr;
  //std::cout << "QUEUE MOVE CONSTRUCTOR" << std::endl; 
  Queue::nodePtr rhsPtr = rhs.head->next;
  while( rhsPtr != rhs.tail )
    {
      this->push( rhsPtr->data ); 
      rhsPtr = rhsPtr->next;
    } // end while
}

// MOVE ASSIGNMENT
// Pre-Condition:
// Post-Condition: empty assignment operator that takes an rvalue reference to
// the class type as its parameter and returns a reference to the class type,
////////////////////////////////////
template <typename T>
typename Queue<T>:: Queue& Queue<T>::operator=( Queue&& rhs )
{
  if( this != &rhs )
    {
      while( !empty() )
	{
	  pop(); // head, tail node markers exists 
	}
      Queue::nodePtr rhsPtr = rhs.head->next;
      while( rhsPtr != rhs.tail )
	{
	  push( rhsPtr->data );
	  rhsPtr = rhsPtr->next;
	} // end while
      while( !rhs.empty() )
	{
	  rhs.pop();
	}
    } 
  return *this;
} 
// DESTRUCTOR
// Pre-Condition: none
// Post-Condition: deallocate memory
////////////////////////////////////
template <typename T>
Queue<T>::~Queue()
{
  //std::cout << "~QUEUE()" << std::endl;
  while( !empty() )
    {
      pop();
    }
  
  delete head;
  delete tail;
}

/*********MUTATORS****************************/
// PUSH
// Pre-Condition: value to insert
// Post-Condition: add a new element val into the end of the current queue. 
////////////////////////////////////////
template <typename T>
void Queue<T>::push( const T& val )
{
  
  Queue::nodePtr newNode = new Node( val );
  Queue::nodePtr currNode = head;
  Queue::nodePtr prevNode = currNode; 
  while( currNode != tail )
    {
      prevNode = currNode;
      currNode = currNode->next;
    }  
  prevNode->next = newNode;
  newNode->next = tail;
  ++nel;
}
// PUSH
// Pre-Condition: none
// Post-Condition: add a new element val into the end of the current queue. val
// should be moved not copied
template <typename T>
void Queue<T>::push( const T&& val )
{
  Queue::nodePtr newNode = new Node( val );
  Queue::nodePtr currNode = head;
  Queue::nodePtr prevPtr = currNode;
  while( currNode != tail )
    {
      prevPtr = currNode;
      currNode = currNode->next;
    }
  // insert at the end of the queue
  prevPtr->next = newNode;
  newNode->next = tail;
  ++nel;
}
// POP
// Pre-Condiiton: none
// Post-Condition: remove the first element in the queue and discard it
/////////////////////////////////////////
template <typename T>
void Queue<T>::pop()
{
  if( !empty() )
    {
      // point to node after head marker
      // points to first node element
      Queue::nodePtr ptr = head->next;
      // relink head to next node
      head->next = ptr->next;
      ptr->next = nullptr;   
      // delete node
      delete ptr;
      // decrement size
      --nel;
    }
}

/***Accessors***/
// SIZE
// Pre-condition: none
// Post-Condition: returns number of elements in queue
template <typename T>
int Queue<T>::size() const
{
  return nel; 
}
// FRONT
// Pre-Condition:
// post-Condition:
////////////////////////////////
template <typename T>
T& Queue<T>::front()
{
  T temp;
  if( !empty() )
    { 
      temp = head->next->data;
      T& retval = temp;
      return retval;
    }
  else
    {
      std::cerr << "**Error: Queue is empty" << std::endl;
      exit( -1 );
    }
}
// CONST FRONT
// Pre-Condition:
// Post-Condition: return reference to first element
/////////////////////////////////
template <typename T>
const T& Queue<T>::front() const
{
  T temp = head->next->data ;
  T & retval = temp;
  if(!empty())
    {
      return retval;
    }
  else
    {
      std::cerr << "**Error: Queue is empty" << std::endl;
      exit( -1 );
    }
}
// BACK
// Pre-Condition:
// Post-Condition: returns reference to last elemnt
//////////////////////////////////////////////
template <typename T>
T& Queue<T>::back()
{
  T temp; 
 Queue:nodePtr currPtr; 
  if( !empty() )
    {
      currPtr = head->next;
      while( currPtr->next != tail )
	{
	  currPtr = currPtr->next;
	}
      temp = currPtr->data;
      T& retval = temp;
      return retval;
    }
  else
    {
      std::cerr << "**Error: Empty Queue" << std::endl;
      exit( -1 );
    }
} 
// BACK
// Pre-Condition:
// Post-Condition: returns const reference to the last element
///////////////////////////////////////////////
template <typename T>
const T& Queue<T>::back() const
{
  T& retval;
 Queue:nodePtr currPtr;
  if( !empty() )
    {
      currPtr = head->next;
      while( currPtr->next != tail )
	{
	  ++currPtr;
	}
      return currPtr;
    }
  exit( -1 );
}
// PRINT
// Pre-Condition:
// Post-Condition: prints out the elemnts of queue
//////////////////////////////////////////////
template <typename T>
void Queue<T>::print() const  
{
  Queue::nodePtr ptr = head->next;
  if( !empty() )
    {
      while( ptr != tail )
	{
	  std::cout << ptr->data << " " ;
	  ptr = ptr->next;
	}
      //  std::cout << '\n' << "NEL: " << nel << std::endl;  
    }
}
// EMPTY?
// Pre-condition:
// Post-Condition:
///////////////////////////////////////
template <typename T>
bool Queue<T>::empty() const
{
  if( nel != 0 )
    {
      return false;
    }
  return true;
}

// OS
// Pre-Condition: stdout, and Queue
// Post-Condition : overload << to print
///////////////////////////////////////
template <typename T>
std::ostream& operator<<( std::ostream &os, const Queue<T> &q )
{
  q.print();
  return os;
} 

