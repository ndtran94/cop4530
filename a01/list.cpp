#include <list.h>
//////////////////
//
//  N O D E 
//
//////////////////
Node::Node()
{
  output = " ";
  next = NULL;
}
//////////////////
//
//  L I S T 
//
///////////////////
List::List()
{
  head = tail = NULL;
}
//////////////////
//
//  I N S E R T
//
///////////////////
void List::insert( std::string* s )
{
  nodePtr newNode = new Node();
  newNode->output = *s;
  newNode->next = NULL;

  if( isEmpty() == true )
    {
      head = tail = newNode;
    }
  else
    {

      nodePtr currentPtr, prevPtr;
      currentPtr = prevPtr = head;
      while( currentPtr != NULL )
	{ 
	  prevPtr = currentPtr;
	  currentPtr = currentPtr->next;
	}
      prevPtr->next = newNode;
      tail = newNode;
      // link list in descending neighbor # order
    }
}
///////////////////////
//
//  C O M P A R E - N E I G H B O R S
//
///////////////////////
/*bool List::compareAs( nodePtr node1, nodePtr node2 )
{
  char *ptr1 = &( node1->output[ 0 ] );
  char *ptr2 = &( node2->output[ 0 ] );
  ptr1 = strtok( &( node1->output[ 0 ] ), " " );
  ptr2 = strtok( &( node2->output[ 0 ] ), " " );
  for( int i = 0; i < 2; ++i )
    {
      ptr1 = strtok( NULL, " ");
      ptr2 = strtok( NULL, " ");
    }
    std::cout << "PTR1: " << ptr1 << std::endl;
    std::cout << "PTR2: " << ptr2 << std::endl;
  if( ptr == ptr2 || ptr1 < ptr2 )
    {
      return false;
    }
  return true;
}
*/
 ////////////////////////
 //
 //  P R I N T - L I S T
 //
 ////////////////////////
 // Pre-Condtion: none
 // Post-Condition: output all of the BGS required output
void List::printList() const
{
  nodePtr currentPtr;
  currentPtr = head;
  while( currentPtr != NULL )
    {
      std::cout << currentPtr->output << std::endl;
      currentPtr = currentPtr->next;
    } 
}
////////////////////////
//
//    i S E M P T Y 
//
///////////////////////
bool List::isEmpty() const
{
  return head == NULL?true:false;
}
