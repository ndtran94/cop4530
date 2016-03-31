
#include <route.h>
#include <list.h>
#include <sstream>
int main()
{
  List orderedList;
  std::string bgs;                  // BGS routing num
  std::vector<std::string> vec;     // Vector of string to store neighbors
  int neighbors;                    // Crreate int variable for # of neighbors to AS
  std::string aspath;               // 7th field of BGS route
  std::string as;                   // Create string variable to store network AS
  std::string outputTxt;            // Place all of the info. into required output txt
  // Read from standard input
  std::getline( std::cin, bgs );
  do{   
    parse_BGS( &bgs, &aspath );      // loop & parse for 7th field
    parse_ASPATH( &aspath, &vec );   // parse the ASPATH into separate fields into vector
    // check for Asset
    // asset located in last char of last vector element
    // if found delete last element in vector
    if( find_ASSET(  &vec ) == true )
      { // do nothing 
      }
    // parse ASPATH for neighboring repeating AS
    check_Neighbors( &vec );
    // set network prefix
    // newtwork prefix is last field in ASPATH
    as = vec[ ( vec.size() -1 ) ];
    int i = 0;
    int x = count_Neighbors( &vec );
    std::stringstream ss;
    ss << x;
    std::string str = " ";
    ss >> str; 
    outputTxt = as + " " + str + " ";
    while( i < ( vec.size() - 1 ) )
      {
	std::string temp;
	temp = vec[ i ] + "|";
	outputTxt = outputTxt + temp;
	++i;
      }
    orderedList.insert( &outputTxt );
    bgs = " ";
    vec.clear();
    neighbors = 0;
    aspath = " ";
    as = " ";
    outputTxt = " ";
  }while( !std::getline( std::cin, bgs ).eof() );
  orderedList.printList();
  return 0;
}
