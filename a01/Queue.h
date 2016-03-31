#ifndedf COP4530_QUEUE_H
#define  COP4530_QUEUE_H
/***********************
 * COP 4530
 * ASSIGNMENT #3
 * Name: Nhi Tran
 *********************/
#include <iostream>
#include <stdexcept>

namespace cop4530
{
  template <typename T>
class Queue
    {
    private:
  struct Node
  {
    T data;
    Node* prev;
    Node* next;
  Node() : data{ 0 }, prev{ nullptr }, next{ nullptr }{}
    Node( const T& d = Node(), Node* p = nullptr, Node* n = nullptr ) 
							: data{ d }, prev{ p }, next{ n }{}
    Node( T&& d, Node* p = nullptr, Node* n = nullptr )
											   : data{ std::move( d ) }, prev{ std::move( p ) }, next{ std::move( n ) }{} 
  public:
    Queue();        // zero parameter constructor. Create an empty queue
    
  private:
    Node* myFront;
    Node* myBack;
    int size;       // current amount of Nodes in Queue 
  }; // end class Queue
#include "Vector.hpp"
    } // end of namspace  COP4530



#endif
