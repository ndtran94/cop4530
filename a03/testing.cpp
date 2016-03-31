#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <utility>
#include "Queue.h"
#include <list>
#include <fstream> 
using namespace std;
using namespace cop4530;

int location( std::string* array, int size, std::string search );
bool cityCheck( std::string* cityArray, std::string start, std::string destination, int numCities );
void printInfo( std::string* cityArray, int numCities, vector<list<pair<string,int>>>&adjacencyList );
		void shortestSearch( std::string* cityArray, int numCities, std::string start, std::string destination, vector<list<pair<string,int>>>&adjacencyList );


				     int main(int argc, char** argv)
				     {
				       ifstream inStream;
				       int numCities;
				       int data; 
				       std::string tempData;
				       /****** Read input file ******/
				       inStream.open( argv[ 1 ] );
				       // get numCities from first line of .input
				       std::getline( inStream, tempData  );
				       numCities = atoi( &tempData[ 0 ] );
				       std::string cityArray[ numCities ];
				       // vector of lists.
				       // each list is a pair: adjacent city, adj. city's price
				       std::vector< std::list< std::pair< std::string, int >>> adjacencyList( numCities );
				       std::list<std::pair<std::string,int>>::iterator itr;
  

				       // read from file of Cities Name
				       for( int  i = 0; i < numCities; ++i )
					 {
					   std::getline( inStream, tempData  );
					   cityArray[ i ] = tempData;
					 }
				       // read file for adjacencyList
				       int j = 0;
				       while( j < numCities )
					 {
					   // read data line by line
					   // size_t i  will tell which cityName for cityArray to insert to pair
					   // read x number of data values on the line 
					   for( int i = 0; i < numCities; ++i )
					     {
					       inStream >> data;
					       if( data > 0 )
						 {
						   // create pair for current city and 
						   std::pair< std::string, int > entry;
						   entry.first = cityArray[ i ];
						   entry.second = data;
						   // insert adjacenct city into vector
						   adjacencyList[ j ].push_back( entry );
						 }// end if
					     } // end of reading for that particular city 
					   ++j;
					 }// move next for adjaceny list
				       /*********** print data ************/
				       printInfo( cityArray, numCities, adjacencyList );
				       /******** prompt *************/
				       char response = ' ';
				       std::string start;
				       std::string destination;
				       std::cout << "\n==================" << std::endl;
  do
    { std::cout << "Source city: ";
      std::getline( std::cin, start  );
      std::cout << "Destination city: ";
      std::getline( std::cin, destination  );
      if( cityCheck( cityArray, start, destination, numCities ) == true )
	{
	  /******* Performing search ************/
	  shortestSearch( cityArray, numCities, start, destination, adjacencyList );
	} 
    do
      {
	std::cout << "Search another route? (Y/N): ";
	std::getline( std::cin, tempData );
	response = tempData[ 0 ];
      }while( response != 'y' && response != 'Y' && response != 'n' && response != 'N' ); 
    }while( response == 'y' || response == 'Y' );
				     }// end main funtion


 
					 /*****************************************/
				     int location( std::string* array, int size, std::string search )
					 {
					   int pos = -1 ;
					   for( int i = 0; i < size; ++i )
					     {
					       if( array[ i ] == search )
						 {
						   pos = i;
						 }
					     }
					   return pos;
					 }                
                 
				       // two differ start and destination
				       // check if start and destination are in cityArray
				       bool cityCheck( std::string* cityArray, std::string start, std::string destination, int numCities )
				       {
					 bool startCheck = false;
					 bool destCheck = false;


					 if( start == destination )
					   {
					     std::cout << "Inputted source and destination are the same" << std::endl;
					     return false;
					   }
					 else
					   {
					     int pos = -1;
					     pos = location( cityArray, numCities, start );
					     if( pos > -1 )
					       {
						 startCheck = true;
					       }
					     pos = location( cityArray, numCities, destination );
					     if( pos > -1 )
					       {
						 destCheck = true;
					       }
					     if( startCheck == false || destCheck == false )
					       {
						 std::cout << "path doesn't exits; ";
						 if( startCheck == false )
						   {
						     std::cout << start << " doesn't exist ";
						   }
						 if( destCheck == false )
						   {
						     std::cout << "; " << destination << " doesn't exist" << std::endl;
						   }
						 return false;
					       }
					   }// end else
					 return true;
				       }

				       void printInfo( std::string* cityArray, int numCities, vector<list<pair<string,int>>>&adjacencyList )
						       {
							 std::list<std::pair<std::string,int>>::iterator itr;
							 std::cout << "Number of Cities: " << numCities << ":" << std::endl;
							 for( int i = 0; i < numCities; ++i )
							   {
							     std::cout << '\t' << cityArray[ i ] << std::endl;
							   }
							 // print out the cities we have
							 std::cout << "\ndirect flights between cities" << std::endl; 
							 std::cout << "---------" << std::endl;
							 int j = 0;
							 while( j < numCities )
							   { 
							     cout << cityArray[ j ] << " : " << std::endl;
							     for(itr = adjacencyList[j].begin(); itr != adjacencyList[j].end(); ++itr)
							       {
								 cout << '\t' << itr -> first << ", $" << itr -> second << ",\n";
							       }    
							     ++j;
							   }
						       }// end print
                
						       void shortestSearch( std::string* cityArray, int numCities, std::string start, std::string destination, vector<list<pair<string,int>>>&adjacencyList )
									    {
 
									      int startPos = location( cityArray, numCities, start );
									      int destPos = location( cityArray, numCities, destination );
									      std::vector<pair<string,int>> predLabel( numCities ); // predecessor
									      std::vector<int> positions;
									      // labels . vector
									      // of pairs
									      int distance = 0; // distance from start vertex
									      std::string vertex; // vertex City
									      Queue< std::string > vertexQueue;
									      std::list<std::pair<std::string,int>>::iterator itr;
									      std::pair< std::string, int > entry;
									      std::pair< std::string, int> first;
									      std::vector< int > distLabel( numCities ); // vector with enough room for
									      // numCities of cities. marked
									      // as unvisited (-1)
									      for( int  i = 0; i < numCities; ++i )
										{
										  distLabel[ i ] = -1;
										}
									      distLabel[ startPos ] = 0;
									      predLabel[ startPos ].first = start;
									      // initialize a queue to only contain start
									      // initialize a queue to only contain start
									      vertexQueue.push( start );
									      // while destination hasn't been vistied, and queue isn't empty
									      while( distLabel[ destPos ] < 0 && !vertexQueue.empty() )
										{
										  vertex = vertexQueue.front(); // initialzie vertex
										  vertexQueue.pop();            // remove vertex from queue
										  int pos = location( cityArray, numCities, vertex ); // get location to
										  // access proper
										  // adjacecny list
										  //    predLabel[ pos].second = vertex.second;   
										  positions.push_back( pos );
										  if( distLabel[ pos ] > distance )
										    {
										      distance++; 
										    }
										  itr = adjacencyList[ pos ].begin();
										  // for loop for adjacent vertexes (w) to v
										  for( int i = 0; i < adjacencyList[ pos ].size()  ; ++i )
										    {
       
										      int pos2 = loca      // add w to the queue
											entry.first = itr->first;
										      entry.second = itr->second;
										      predLabel[ pos2 ].first = entry.first;
										      predLabel[ pos2 ].second = entry.seor( int i = distance -1; i > 0; --i ) 
											{
											  path[ i ].first = predLabel[ positions.back() ].first;
											  path[ i ].second = predLabel[ positions.back() ].second;
											  positions.pop_back();

											}  
										      for( int i = 0; i < path.size(); ++i )
											{
											  cost = cost + path[ i ].second;
											  std::cout << path[ i ].first << "-->"; 
											}
										      std::cout << "; $ " << cost << std::endl << std::endl;
										    }
										}
