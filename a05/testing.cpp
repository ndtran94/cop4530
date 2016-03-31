#include <iostream>
#include "hashtable.h"
using namespace cop4530;

int main()
{
  size_t x = 5;
  string val = "200";
  string val2 = "1";
  string val3 = "30";
  string val4 = "abc";
  string val5 = "4";
  string val6 = "60";
  string val7 = "900";
  string val8 = "-90";
  string val9 = "9000";
  string val10 = "1092";
  string val11 = "vall11"; 
  HashTable<string> test(x);
  test.insert( val );
  test.insert( val2 );
  test.insert( val3 );
  test.insert( val4 );
  test.insert( val5 );
  std::cout << "HERE... " << std::endl;
  test.dump();
  test.insert( val6 );
  test.insert( val7 );
  test.insert( val8 );
  test.insert( val9 );
  test.insert( val10 );
  test.insert( val11 );
  std::cout << ".....calling dump: " << std::endl;
  test.dump();

  std::cout << "========================" << std::endl;
  std::cout << "......testing remove(200)" << std::endl;
  test.remove( val );
  std::cout << "......print out:" << std::endl;
  test.dump();
  std::cout << "========================" << std::endl;
  std::cout << "after clear:: " << std::endl;
  test.clear();
  test.dump();
  test.load("file1.txt");  
  std::cout << ":::::::::::::::::" << std::endl;
  test.dump();
  test.write_to_file( "outfile.txt" ); 
}
