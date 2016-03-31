#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <iterator>
#include <fstream>
#include <string>
// used when improper size is given (for example
// size is 0 or negatiave)

static const unsigned int default_capacity = 11;
static const unsigned int max_prime = 1301081;

using namespace std;
 
namespace cop4530
{ 
  template <typename T>
  class HashTable
    {
    public:
      HashTable         ( size_t = 101  ); // Constructor
      ~HashTable        ();                // Destructor
      bool contains     ( const T &     ); // Check if x is in hash table
      bool insert       ( T& );            // add x into hashtable.No duplicates
      bool insert       ( T&& );      // move x into hashtable. No duplicates
      bool remove       ( const T & x ); // add x if in hash table
      void clear        ();              // delete all elements
      bool load         ( const char *); // load content of file 
      void dump         ();              // display all entries into table
      bool find         ( const T&  ); 
      bool write_to_file( const char *filename ); // write all elements 
      size_t returnCount(){ return count; }   
    private:
      std::vector< std::list< T > > bucketVector;// vector of Lists
      unsigned long prime_below(unsigned long);
      void          setPrimes  (std::vector<unsigned long> &);  
      size_t count;        // number of elements          
      void          makeEmpty(); // delete all elements. clear() will call this 
      void          rehash   (); // rehash. called when number of elements in hash table is
      // greater than the size of the vector
      size_t        myhash      ( const T&  ); // return index of vector entry where x should
      // be stored
      unsigned int  hashfunction( const T& ); // returns hash index  
    }; // end class
#include "hashtable.hpp"
}; // end namespace 

#endif
