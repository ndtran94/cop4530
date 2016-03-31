#include  "hashtable.h"

//
// PRIME BELOW
// Pre-Condition:
// Post-condition: returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cout << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
      std::cout << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
        return n;
      --n;
    }

  return 2;
}

//
//
// SET PRIMES
// Pre-Codition: 
// Post-Condition: determine the proper prime numbers used in setting up the
// vector size. 
// Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

/*************** PRIVATE INTERFACE **************/ 

//
// HASH FUNCTION
// 
//
template <typename T>
unsigned int HashTable<T>::hashfunction( const T& x )
{
  unsigned int i;
  long unsigned int bigval = x[ 0 ]; // S[0] or '\0'
  for (i = 1; i < x.size(); ++i)
    bigval = ((bigval & 65535) * 18000)    // low16 * magic_number
      + (bigval >> 16)              // high16
      + x[ i ];
  bigval = ((bigval & 65535) * 18000) + (bigval >> 16);
  // bigval = low16 * magic_number + high16
  return bigval & 65535;
  // return low16
} 

//
// MYHASH
//
//
// Post-Condition: returns the index of the vector entry where should be entered
template <typename T>
size_t HashTable<T>::myhash( const T& x )
{
  return hashfunction( x ) % bucketVector.capacity();
}
//
//
// MAKE EMPTY
// Post-Condition: delete all elements in the hashtable. Called by clear()
template <typename T>
void HashTable<T>::makeEmpty()
{
  if( count > 0 )
    {
      for( int i = 0; i < bucketVector.capacity(); ++i )
	{
	  typename std::list< T >::iterator itr1 = bucketVector[ i ].begin();
	  typename std::list< T >::iterator itr2 = bucketVector[ i ].end();
	  while( itr1 != itr2 )
	    {
	      itr1 = bucketVector[ i ].erase( itr1 );
	      --count;
	    }// end while
	}// end for
    }// end if
} // end function

/*************** PUBLIC INTERFACE  **************/
//
//
// CONSTRUCTOR
// Pre-Condition:
// Post-Condition: Creat a hash table . size of vector set to prime_below(size) 
template <typename T>
HashTable<T>::HashTable( size_t x )
{
  bucketVector.resize( prime_below( x ));
  count = 0;
}
//
// DESTRUCTOR
// Pre-Condition: allocated vector of lists
// Post-Condition: deallocate
template <typename T>
HashTable<T>::~HashTable()
{
  clear();
}
//
//
// CONTAINS
// Pre-Condition: pass value to search for
// Post-Condiiotn: returns true if value is found in list
template <typename T>
bool HashTable<T>::contains( const T& x )
{
  if( count == 0 )
    {
      return false;
    }
  typename  std::list< T >::iterator itr;
  int pos = myhash( x );
  for( itr = bucketVector[ pos ].begin(); itr != bucketVector[ pos ].end(); ++itr )
    {
      if( *itr == x )
	{
	  return true;
	}
    }
  return false;
}
//
// REHASH
// Pre-condition: number of elements is greater than vector size
// Post-Condition: double size of vector
template <typename T>
void HashTable<T>::rehash()
{
  // copy elements from vector into a temp vector
  std::vector<T> elements;
  typename std::list< T >::iterator itr1;
  typename std::list< T >::iterator itr2;
  for( int i = 0; i < bucketVector.capacity(); ++i )
    {
      itr1 = bucketVector[ i ].begin();
      itr2 = bucketVector[ i ].end();
      // store elements in a temporary vector 
      while( itr1 != itr2 )
	{
	  elements.push_back( *itr1 );
	  ++itr1;
	}  
    }
  // empty bucketVector
  // resize bucketVector
  size_t  newSize = prime_below( bucketVector.capacity() * 2 );
  clear();
  bucketVector.resize( 0 );
  bucketVector.resize( newSize );
  // push elements back into resized bucket 
  for( int i = 0; i < elements.size(); ++ i )
    {
      this->insert( elements[ i ] );
    }   
}
//
//
// INSERT
//
// Pre-Condition: value doesnt already exists
// Pos-tCondition : returns true if inserted
template <typename T>
bool HashTable<T>::insert( T& x )
{
  if( !contains( x ) )
    {
      // insert item
      size_t pos = myhash( x );
      bucketVector[ pos ].push_back( x );
      ++count;
      // rehash when number of elements in the hash table is greater than the size
      // of the vector
      if( count > bucketVector.size() )
	{
	  rehash();
	}
      return true;
    }// end if
  return false;
}
//
// INSERT MOVE
// Pre-condition:
// Post-Condtion: move content into hashtable
template <typename T>
bool HashTable<T>::insert( T && x )
{
  if( !contains( x ) )
    {
      // insert item
      size_t pos = myhash( x );
      bucketVector[ pos ].push_back( std::move( x ) );
      return true;
      ++count;
      // rehash when number of elements in the hash table is greater than the size
      // of the vector
      if( count > bucketVector.size() )
	{
	  rehash();
	}
      return true;
    }
  return false;
}
//
// REMOVE
// Pre-Condition: list of bucketVector entry exists
// Post-condtion: returns true if removed
template <typename T>
bool HashTable<T>::remove( const T& x )
{
  if( !contains( x ) )
    {
      return false;
    }
  // bucketVector contains item
  // search bucket entry for item
  int pos = myhash( x );
  typename std::list< T >::iterator itr;
  for( itr = bucketVector[ pos ].begin(); itr != bucketVector[ pos ].end(); ++ itr )
    {
      if( *itr == x )
	{
	  itr = bucketVector[ pos ].erase( itr );
	  --count;
	  return true; 
	} // end if
    } // end for
}
//
//
// CLEAR
// Pre-condition: elements in hashtable
// Post-Condtiion: delete all elements in the hash table
template <typename T>
void HashTable<T>::clear()
{
  makeEmpty();
}

//
//
// DUMP
// Pre-Condition: a vector Bucket hass been created
// post-Condition: print out the contents of each list of Vector Bucket
template <typename T>
void HashTable<T>::dump()
{
  typename std::list< T >::iterator itr;
  for( int i = 0; i < bucketVector.size(); ++i )
    {
      std::cout << "bucketVector[ " << i << " ]: " ;
      for( itr = bucketVector[ i ].begin(); itr != bucketVector[ i ].end(); ++itr )
	{
	  std::cout << *itr << " ";
	}
      std::cout << std::endl; 
      nable to open file: " << filename << std::endl;
    return false;
  }
  std::string entry;
  while( inFile >> entry )
  {
    insert( entry );
   }// end while*/
  inFile.close();
  return true;
} 
//
// WRITE TO FILE
//
// Post-Condition: append file to write all of hashtable elements into outfile
template <typename T>
bool HashTable<T>::write_to_file( const char* filename )
{
  ofstream outFile;
  typename std::list< T >:nd( const T& x )
{
  if( contains( x ) == true )
  {
    std::cout << "Word " << x << "found." << std::endl;
    return true;
  }
  std::cout << "Word " << x << "not found." << std::endl;
  return false;
}   

