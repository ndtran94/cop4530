#include <iostream>
#include <algorithm>

//////////////////////////////
//
//  C O N S T R U C T O R S
//
//////////////////////////////

//  D E F A U L T  -  C O N S T R U C T O R
// Pre-Condition: zro parameter constructor
// Post-Condition: Create an empty vector. Initialize size=capacity=0. ptr=nullptr
template <typename T>
Vector<T>::Vector()
{
  theSize = theCapacity = 0;
  array = nullptr;
}
// D E S T R U C T O R
template <typename T>
Vector<T>::~Vector()
{
  //  std::cout << "Deconstructor.." << std::endl;; 
  delete [] array;
}
// C O P Y  C O N S T R U C T O R
// Pre-Condition: passes Vector object to copy
// Post-Condition:
template <typename T>
Vector<T>::Vector( const Vector & rhs ): theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, array{ nullptr }
{
  Vector();
  for( auto & x : rhs )
    {
      push_back( x );
    }
}

// C O P Y - A S S I G N M E N T
template <typename T>
const typename Vector<T>:: Vector& Vector<T>::operator=(const Vector &rhs)
{
  Vector<T> copy = rhs;
  std::swap( *this, copy );
  return *this;
}
//  M O V E  -  C O N S T R U C T O R
template <typename T>
Vector<T>::Vector( Vector && rhs ): theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity}, array{ nullptr }
{
  array = new T[theCapacity];
  for( int i = 0 ; i != theSize; ++i )
    {
      array[ i ] = rhs.array[ i ];
    }
  rhs.array = nullptr;
  rhs.theSize = 0;
  rhs.theCapacity = 0;
}
// M O V E  -  A S S I G N M E N T
template <typename T>
typename Vector<T>::Vector& Vector<T>::operator=(Vector &&rhs)
{
  std::swap( theSize, rhs.theSize );
  std::swap( theCapacity, rhs.theCapacity );
  auto itr = rhs.begin();
  int i = 0;
  while( itr != rhs.end() )
    {
      std::swap( itr, &(rhs.array[ i ]));
      ++itr;
    }
}

// E X P L I C I T - C O N S T R U C T O R
// Pre-condition: Construct a Vector with n elements
// Post-Condition: all initialized with value val
template <typename T>
Vector<T>::Vector( int n, const T& val )
{
  theSize = theCapacity = n;
  array = new T[ theCapacity ];
  for( int i =0 ; i < n; ++i )
    {
      array[ i ] = val;
    }
  
}
// S T A R T   T O  E N D  C O N S T R U C T O R
// construct a vector with elements from another Vector between start and end. Including the element refererred by the start iteraor, but not end
template <typename T>
Vector<T>::Vector( const_iterator start, const_iterator end )
{
  theSize = 0;
  theCapacity = 0;
  array = new T[ theCapacity ];
  const_iterator x = start;
  while( x != end )
    {
      push_back( *x );
      ++x;
    }  
} 
//  P R I N T
//  Pre-Conditin: ostream. ofc: the deliminator bettween eelements of the vector
template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const
{
  if( empty() )
    {
      std::cout << "is empty " << std::endl;
    }
  else
    {
      auto itr = begin();
      auto itr2 = end();
      while( itr  != itr2 )
        {
          os << ofc << *itr;
          ++itr;
        }
    }
}
//
//
//  A C C E S S O R S
//
//
// I N D E X  O P E R A T O R
// Pre-Condition: integer location index
// Post-Condition: Return reference to the element at the specified location
template <typename T>
T& Vector<T>::operator[](int index)
{
  // no error checking
  return array[ index ];
}
//  C O N S T  I N D E X[ ] 
template <typename T>
const T& Vector<T>::operator[](int index) const
{
  // no error checking
  return array[ index ];
}
//  A T  F U N C T I O N
// Pre-conditino: index loc
// post-condition: returns reference to the element at the specified location
// Throw "out_of_Range" exception if index is not in the valid [0,thesize]
template <typename T>
T& Vector<T>::at( int loc )
{
  if( theSize == 0 || loc >= theSize || loc < 0 )
    {
      std::cout << "out_of_range" << std::endl;
      return this;
    }
  return &array[ loc ];
}
// C O N S T  A T  F U N C T I O N
// Pre-conditino: index loc
// post-condition: returns const reference to the element at the specified location
// Throw "out_of_Range" exception if index is not in the valid [0,thesize]
template <typename T>
const T& Vector<T>::at( int loc ) const
{
  if( theSize == 0 || loc >= theSize || loc < 0 )
    {
      std::cout<< "out_of_range" << std::endl;
      return this;
    }
  return &array[ loc ];
}
// T &  F R O N T
// Pre-Condition:
// Post-Condition: returns reference to the first element
template <typename T>
T & Vector<T>::front() // reference to the first element
{
  T& ref = array [ 0 ];
  return ref;
}
// C O N S T  T &  F R O N T
// Pre-Condition:
// Post-Condition: returns reference to the first element
template <typename T>
const T& Vector<T>::front() const
{
  T& ref = array[ 0 ];
  return ref;
}
// T &  B A C K 
// Pre-Condition:
// Post-Condition: returns reference to the last  element
template <typename T>
T & Vector<T>::back() // reference to the last element
{
  if( theSize == 0 )
    {
      T& ref = array[ 0 ];
      return ref;
    }
  T& ref = array[ theSize - 1 ];
  return ref;
}
// C O N S T   T &  B A C K
// Pre-Condition:
// Post-Condition: returns reference to the last  element
template <typename T>
const T & Vector<T>::back() const
{
  T& ref = array[ theSize - 1];
  return ref;
} 

// D O U B L E  C A P A C I T Y
// Pre-Condition: 
// Post-Condition: double the capacity of vector 
template <typename T>
void Vector<T>::doubleCapacity()
{
  // if current capacity += 0 , new capacity == 0
  if( theCapacity == 0 )
    {
      ++theCapacity;
    }
  else
    {
      theCapacity = (theCapacity * 2);
    }
}
// S I Z E 
// Pre-Condition:
// Post-Condtion: return the number of elements stored in the vector
template <typename T>
int Vector<T>::size() const
{
  return theSize;
}
// C A P A C I T Y
// Pre-Condition:
// Post-Condition: returns theCapacity stored in the vector
template <typename T>
int Vector<T>::capacity() const
{
  return theCapacity;
}
// E M P T Y
// Pre-Condition:
// Posst-Condition: returns true if Vector is empty
template <typename T>
bool Vector<T>::empty() const
{
  if( theSize == 0 )
    {
      return true;
    }
  return false;
}

//
//
//   M U T A T O R
//
//
//
//  R E S I Z E
// Pre-Condition: num = newSize, newValue placed into new positions
template <typename T>
void Vector<T>::resize( int num, T val  )
{
  
  if( num > theCapacity || num == theCapacity )
    {
      int oldSize = theSize;
      doubleCapacity();
      reserve( theCapacity );
      while( oldSize < theCapacity )
        {
          array[ oldSize ] = val;
          ++oldSize;
        }

    }
}
//  R E S E R V E
// Pre-Condition: takes the size and create a new array
template <typename T>
void Vector<T>::reserve( int size )
{
  if( size > theSize )
    {
      T *newArray; 
      newArray = new T[ size ];
      for( int i = 0; i < theSize; ++i )
        {
	  newArray[ i ] = std::move( array[ i ] );
        }
      theCapacity = size;
      std::swa theCapacity, val );
}
array[ theSize ] = std::move( val );
++theSize; 
}

// P O P - B A C K 
// Pre-Condition:
// Post-Condition: deletes last element off the array
template <typename T>
void Vector<T>::pop_back()
{
  // delete last element in the vector
  if( !empty() )
    {
      --theSize;
    }
}
// C L E A R
template <typename T>
void Vector<T>::clear()
{
  while( !empty() )
    {
      pop_back();
    }
}


//
//
// I T E R A T O R - S U P P O R T 
//
// 
// I T E R A T O R  B E G I N
template <typename T>
typename Vector<T>::iterheSize ];
}
// I T E R A T O R - I N S E R T
// Pre- Condition: insert itr position, value to insert
// Post- Condition: insert value adead of itr. Return value is an iterator represeting the position of inserted item
template <typename T>
typename Vector<T>::iterator Vector<T>::insert( iterator pos, const T& val )
{
  if( theSize == theCapacity )
    {
      resize( theCapacity );
    }
  iterator& a =  pos;
  std::cout << "a: " << *a << std::endl;
  iterator b = end() ;
  iterator c = end() - 1;
  
  int i = size();
  while( b != a )
    {
      *b = *c;
      --c;     
      --b;
      --i;
    }
  array[ i ] = std::move( val );
  ++theSize;  
  return &array[ i ];
}
// I T E R A T O R - E R A S E
// Pre-Condition: iterator is the va = size() - 1;
while( i < stop )
  { 
    *pos = *++next;
    ++pos;
    ++i;
  }
--theSize;
// return the iterator prior erased element at position
return &array[ size() - i ];
}
// I T E R A T O R : S T A R T - E R A S E
// delete all elements between start and end including start, not end
// return value is the iterator following the last element being deleted
template <typename T>
typename Vector<T>::iterator Vector<T>::erase( iterator start, iterator end )
{

  iterator itr = --end;
  while( itr != start )
    { 
      itr = ;
    }
}
 else
   {
     return false;
   }
return true;
}
// !=
template <typename T>
bool operator!=( const Vector<T> & lhs, const Vector<T> &rhs )
{
  if( !(lhs == rhs ) )
    {
      return true;
    }
  return false;

}
// O S T R E A M
template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v)
{
  v.print( os );
  return os;
}
