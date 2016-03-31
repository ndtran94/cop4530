#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <fstream>
namespace cop4530{
  template <typename T>
  class Queue
    {
    private:
    struct Node
    {
      Node() 
      : data{0}, next{ nullptr }{} 
      Node( const T&val ) 
				  : data{ val }, next{ nullptr }{}
      Node( const T&& val )
								  : data{ std::move(val) },next{ nullptr }{}
      T data;
      Node* next;
    };// end struct
    typedef Node* nodePtr;
    public:
    /**********Constructors*************/
    Queue();                              // Default Constructur 
    Queue( const Queue& rhs );            // Copy Consturctor
    Queue( Queue&& rhs );           // Move Constructor
    const Queue& operator=( const Queue& rhs ); // Copy Assignment
    Queue& operator=( Queue&& rhs );// Move Assignment 
    ~Queue();                             // Destructor
    
    /**************Accessors***********/
    int size() const;        // return number of elements in the current queue
    bool empty() const;      // return if nel  == 0  
    T& front();              // return reference to first element queue
    const T& front() const;  // ret first element reference.  Not head marker                                 
    T& back();               // returns last elemnt - not end marker
    const T& back() const;   // returns last element
    /************* Mutators***********/
    void pop();                           // remove 1st in the queue and discard it
    void push( const T& val );            // add new element val to end of the current queue
    void push( const T&& val );              // add a new element val into the end of the queue
    void print() const;
    private:
    int nel;
    nodePtr head;
    nodePtr tail;
    }; // end Queue class
  template <typename T>
    std::ostream & operator<<( std::ostream & os, const Queue<T>& ); 
#include "Queue.hpp"
} // end namespace



#endif
