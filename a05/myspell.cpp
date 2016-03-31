#include "hashtable.h"
#include <iostream>
#include <string>
using namespace cop4530;
using namespace std;
void menu();

int main()
{

  HashTable<std::string> dictionaryHash;
  char choice = ' ';
  std::string filename;
  std::string checkFile;
  std::string outFile; 
  std::fstream myfile;
  std::ofstream outfile;
  std::string word; 
  // spell checker
  std::cout << "***Spell Checker***" << std::endl;
  std::cout << "Enter filename of dictionary: ";
  std::cin >> filename;
  std::cout << "Enter CheckFile: ";
  std::cin >> checkFile;
  std::cout << "Enter outfile where content will be printed: ";
  std::cin >> outFile; 
  std::cout << "\n\n"; 
  // checkfile compare to dictionary (Filename)
  // open checkFile
  myfile.open( &checkFile[0], ios::in );
  outfile.open( &outFile[0], ios::out );
  bool opens;
  opens = dictionaryHash.load( &filename[ 0 ] );
  // read line by line of checkFile
  if( !myfile )
    {
      std::cout << "**Error: " << checkFile << " does not open" << std::endl; 
    }

  if( myfile.is_open() && opens == true  )
    { 
      while( !myfile.eof() )
	{
	  myfile >> word;
	  // if word is in contains( x ) = valid
	  if( dictionaryHash.contains( &word[ 0 ] ) == true )
	    {
	      // write out onto outFile
	      outfile << word << "\n";
	    }
	  else
	    {
	      // find canidate words
	      std::vector<std::string> candidateWords;
	      std::string correctedWord; 
	      //     find_candidateWords( dictionaryHash, candidateWords, word );
	      // output all of the candidate words
	      std::string invalidWord = word;
	      std::string changedWord = word;
	      int maxCapacity = 10;
	      int maxAlpha = 26;
	      char alphabet[ 26 ] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
				      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	      int i = 0;
	      for( i =0; i < word.length(); ++i )
		{
		  invalidWord[ i ] = toupper( invalidWord[ i ] );
		}
	      // identify 10 canidate words
	      std::cout << "\n\n**Invalid word: " << invalidWord << std::endl;
	      int j = 0;
	      while(  j < word.length() )
		{
		  int i = 0;
		  for( i = 0; i < word.length()-1; ++i )
		    {
		      changedWord[ i ] = word[ i ];
		    }
		  i = 0;
		  while( i < maxAlpha && candidateWords.size() <= maxCapacity )
		    {
            
		      // replace  character
		      changedWord[ j ] = alphabet[ i ];
		      // check if contains
		      if( dictionaryHash.contains( changedWord ) == true )
			{
			  // if true - store into canidateWords vector
			  candidateWords.push_back( changedWord );
			}
		      ++i;
		    }// end while
		  ++j;
		}//end while j < length
	      // output vector of canidate wordsd
	      std::cout << "\n--Candidate words Found--" << std::endl; 
	      for( int i = 0; i < candidateWords.size(); ++i )
		{
		  int k = i + 1;
		  std::cout << k << ":" << candidateWords[ i ] << std::endl;
		}
	      int idx;
	      std::string choiceDo;
	      std::cout << "\nChoose the candidate word's number to add into output file or 'n' if no change:" ;
	      std::cin >> choiceDo;
	      idx = atoi( &choiceDo[0] );
	      if( idx > 0 && idx < 11 )
		{
		  outfile << candidateWords[ idx - 1 ] << "\n";
		}
	      else
		{
		  std::cout << "\n**output to file unchanged word. " << std::endl;
		  outfile << word << "\n";
		}
      
	    }//end else
	}//end while
    
      myfile.close();
      outfile.close();
    }
  std::cout << "*** end of spell checker ***" << std::endl;
  int hashtCapacity;  
  std::cout << "Enter capacity for hash table: ";
  std::cin >> hashtCapacity; 
  HashTable< string > hasht( hashtCapacity );
  do
    {
      do{
	menu();
	std::cin >> choice;
	choice = toupper( choice );
      } while( choice != 'L' && choice != 'A' && choice != 'R' && choice != 'C'
             && choice != 'F' && choice != 'D' && choice != 'S' && 
	       choice != 'W' && choice != 'X' ); 
      std::string entry;
      if( choice != 'X' )
	{
	  switch ( choice )
	    {
	    case 'L':
	      std::cout << "Enter dictionary filename to load from: ";
	      std::cin >> entry;  
	      hasht.load( &entry[0] );
	      break;
	    case 'A':
	      // insert word into hash
	      std::cout << "Enter word: ";
	      std::cin >> entry;
	      hasht.insert( entry );   
	      break;
	    case 'R':
	      std::cout << "\n***Enter word: ";
	      std::cin >> entry;
	      hasht.remove( entry );
	      break;
	    case 'C':
	      std::cout << "\n***Clearing... " << std::endl;
	      hasht.clear();
	      break;
	    case 'F':
	      std::cout << "\n***Enter word: ";
	      std::cin >> entry;
	      hasht.find( entry ); 
	      break;
	    case 'D':
	      std::cout << "\n***Entry... " << std::endl;
	      hasht.dump();
	      break;
	    case 'S':
	      std::cout << "\n***Size of hashtable: " << hasht.returnCount() << std::endl;        break;
	    case 'W':
	      std::cout << "Enter dictionary filename to write to: ";
	      std::cin >> entry;
	      hasht.write_to_file( &entry[0] );
	      break;
	    }
	}// end if
      entry = " ";
    }while( choice != 'X' ); // exit loop at 'X'
}



///////////////////////////////////
void menu()
{
  cout << "\n\n";
  cout << "l - Load Dictionary From File" << endl;
  cout << "a - Add Word" << endl;
  cout << "r - Remove Word" << endl;
  cout << "c - Clear HashTable" << endl;
  cout << "f - Find Word" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
