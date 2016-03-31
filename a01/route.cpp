#include <route.h>
/////////////////////////////
//
//  P A R S E  _  B G S
//
////////////////////////////
// Pre-Condition: pass standard input-BGS num from main to change ASPATH by main
// Post-Condition: change 
void parse_BGS( std::string* bgs, std::string*aspath )
{
  char *ptr = &bgs[ 0 ][ 0 ];
  ptr = strtok( &bgs[ 0 ][ 0 ], "|" );
  for( int i = 0; i < 6; ++i )
    {
      // parse BGS routing number for ASPATH
      ptr = strtok( NULL, "|" );
    }
  *aspath = ptr;
}
////////////////////////////
//
//  P A R S E _ A S P A T H
//
////////////////////////////
// Pre-Condition: Pass ASPATH string, and reference to vector
// Post-Condition: Parse ASPATH string, and push_back fields into vector
void parse_ASPATH( std::string* aspath, std::vector<std::string> *v )
{
  char *ptr = &aspath[ 0 ][ 0 ]; // char pointer to first char of first word in ASPATH
  ptr = strtok( &aspath[ 0 ][ 0 ], " " ); // parse ASPATH into fields. Separate by whitespace
  while( ptr != NULL )
    {
      if( ptr != NULL )
	{
	  v->push_back( ptr );
	}
      ptr = strtok( NULL, " ");
    }
}
///////////////////////////
//
//  F I N D _ A S S E T
//
///////////////////////////
// Pre-Condition: Pass ASPATH string. Look for "[" "] , 
// Post-Condition:
bool find_ASSET( std::vector<std::string>* v )
{
  // ASSET occurs in the end
  // check last char of last vector element        
  int fieldLen = ( strlen( &v[ 0 ][ v->size() - 1 ][ 0 ] ));
  char endChar = v[ 0 ][ v->size() - 1 ][ fieldLen -1 ] ;
  // ASSET exists
  if( endChar == ']' )
    {
      // delete end portion of ASSET
      v->pop_back();
      // traverse backwards through vector element to element
      int elem = v->size() - 1;
      int x = 0;
      while( elem > 0 ) // loop through all elements in vector
        {
          fieldLen = strlen( &v[ 0 ][ elem ][ 0 ] );
          while( x < fieldLen )
            {
              endChar = v[ 0 ][ elem ][ x ];
              if (endChar == '[' ) // front end of ASSET found. Delete element found in
                {
                  v->pop_back();
                  return true;
                } // end if
              ++x;
            } // end while loop looking through character   
          --elem;
        }// end while
    }// end if
  // no ASSET exists
  return false;
}
///////////////////////////////
//
//  C H E C K _ N E I G H B O R S
//
///////////////////////////////
// Pre-Condition:
// Post-Condition:
void check_Neighbors( std::vector<std::string> *v )
{
  // AS number appears multiple times, appear together
  std::string* field1;
  std::string* field2;
  int i = 0;
  int size = v->size();
  if( size > 1 )
    {
      while( i != v->size() )
        {
	  field1 = &v[ 0 ][ i ];
	  field2 = &v[ 0 ][ i + 1 ];
	  if( *field1 == *field2 )
	    {
	      int match = 0;
	      while( match == 0 && i != (v->size()-1) )
		{
		  v->erase( v->begin() + ( i + 1 ) );
		  field1 = &v[ 0 ][ i ];
		  field2 = &v[ 0 ][ i + 1 ];
		  if( *field1 != *field2 )
                    {
		      match = -1;
                    } // end if
		}
                
	    }// end if
	  ++i;
        } // end while
    } // end if
}
////////////////////////////
//
//  C O U N T  N E I G H B O R S
//
/////////////////////////////
int count_Neighbors( std::vector<std::string>* v )
{
  // Neighbors are in pairs
  int numNeighbors = ( v->size() ) - 1;
  return numNeighbors;
}
