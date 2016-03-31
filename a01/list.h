#ifndef LIST_H
#define LIST_H
#include <iostream>
class Node
{
 public:
  Node();
  std::string output;
  Node* next;          
};
typedef Node* nodePtr;
class List
{
 public:
  List();
  void insert( std::string * );
  bool isEmpty() const;
  void printList() const;
 private:
  nodePtr head;
  nodePtr tail;
};
#endif
