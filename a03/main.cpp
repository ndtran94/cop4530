#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include "Queue.h"


using namespace std;
using namespace cop4530;

int main() {
  Queue<int> q1;
  int num =  10;
  int num2 = 20;
  int num3 = 30;
  std::cout << "TESTING PUSH AND DEFAULT CONSTRUCTOR" << std::endl;
  q1.push( num );
  q1.push( num2 ); 
  q1.push( num3 );
  q1.print();  

  std::cout << "\n============" << '\n' << '\n' << std::endl;
  std::cout << "TESTING COPY CONSTRUCTOR" << std::endl;
  Queue<int>q2(q1); 
  std::cout << q2 << std::endl;

  std::cout << "============"<< std::endl;
  Queue<int>q3;
  int num4 = 40;
  int num5 = 50;
  q3.push( num4 );
  q3.push( num5 );
  std::cout << "print: ";
  q3.print();
  std::cout << '\n' << '\n' << "TESTING COPY ASSIGNMENT" << std::endl;
  std::cout << "Q3: ";
  std::cout << q3 << std::endl; 
  std::cout << "print: ";
  q3.print();
  q3 = q1; 
  std::cout <<'\n' << "Q3: ASSIGNMENT: " << q3 << std::endl;
  
  std::cout << "\n============" << std::endl;
  std::cout << "TESTING MOVE ASSIGNMENT: " << std::endl;
  Queue<int>q4;
  std::cout << "Q3: " << q3 << std::endl;
  q4 = std::move( q3 );
  std::cout << "Q4: " << q4 << std::endl; 
  std::cout << "Q3: " << q3 << std::endl;  
  std::cout << "============" << '\n' << '\n' << std::endl;
  std::cout << "TESTING MOVE Q4 TO Q5" << std::endl;
  Queue<int>q5(std::move(q4));
  std::cout << "q5: " << q5 << std::endl;
  std::cout << "q4: " << q4 << std::endl;  
  std::cout << "q4 front: " << q4.front() << std::endl;
  std::cout << "q4 back: " << q4.back() << std::endl;
  return( EXIT_SUCCESS);
}
