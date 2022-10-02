/** @file List.cpp
 * @brief Implementations of member functions of the List
 *   of ints class for the Assignment Overloading and Templates
 *
 * @author Jane Programmer
 * @note   class: COSC 2336, Summer 2021
 * @note   ide  : VSCode Server 3.9.3, Gnu Development Tools
 * @note   assg : Assignment Overloading and Templates
 * @date   June 1, 2021
 *
 * Implementations of a List of ints ADT.  Sort of a preview
 * of some of the data structures and abstract data types we
 * will be learning to build and understand.
 */
#include "List.hpp"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/** @brief  Default constructor
 *
 * Construct an empty list.  The empty list will have no allocated memory
 * nor any values.
 */
template<class T>
List<T>::List()
{
  // Empty list has no values nor any allocated memory
  // associated with it
  this->size = 0;
  this->allocationSize = 0;
  values = nullptr;
}

/** @brief Standard constructor
 *
 * Construct a list of integer values from a (statically) defined and
 * provided array of integers.  We simply allocate a block of memory
 * dynamically large enough to hold the values, then copy the values
 * from the input parameter into our own private array of values.
 *
 * @param size The size of the input values were are given as well as the
 *   size of the new list we are to construct.
 * @param values The (static) array of string values to use to construct
 *   this List values with.
 */
template<class T>
List<T>::List(int size, T values[])
{
  // dynamically allocate a block of memory on the heap large enough to copy
  // the given input values into
  this->size = size;
  this->allocationSize = size;
  this->values = new T[allocationSize];

  // copy the values from the input paramter into our new shiny block of memory
  for (int index = 0; index < size; index++)
  {
    this->values[index] = values[index];
  }
}

/** @brief Copy constructor
 *
 * Provide a copy constructor for the List class.  A copy constructor
 * will be invoked whenver you assign one instance of a List to another.
 * For example
 *   List newList = existingList;
 * Where of course existingList was a previously created List.  This copy
 * constructor, as the name suggests, should make a copy of the values from
 * the given input list into a new List instance.
 *
 * @param list The other List type we are to make a copy of in this
 *   constructor.
 */
template<class T>
List<T>::List(const List<T>& list)
{
  // copy the size of the existing list and allocate memory to hold
  // values we will copy
  size = list.size;
  allocationSize = list.allocationSize;
  values = new T[allocationSize];

  // copy the values from the input List into this list
  for (int index = 0; index < size; index++)
  {
    values[index] = list.values[index];
  }
}

/** @brief Class destructor
 *
 * Destructor for the List class.  A List may (or may not) have
 * a dynamically allocated block of memory associated with it.
 * Free up this block on destruction of a List instance.
 */
template<class T>
List<T>::~List()
{
  // if values is not null, it points to a dynamic block of memory, so
  // delete that block.
  if (values != nullptr)
  {
    delete[] values;
  }
}

/** @brief overload output stream operator for List type.
 *
 * Overload the output stream operator so that we can display current
 * values of a List on standard output.
 *
 * @param out The output stream we should send the representation
 *   of the current List to.
 * @param rhs The List object to create and return a string
 *   representation of on the output stream.
 *
 * @returns ostream& Returns a reference to the originaly provided
 *   output stream, but after we  have inserted current List
 *   values / representation onto the stream
 */
template<typename U>
ostream& operator<<(ostream& out, const List<U>& rhs)
{
  // reuse List str() method to stream to output stream
  // out << rhs.str(); // uncomment this after templatizing str() if want output operator for List

  // return the modified output stream as our result
  return out;
}

/** @brief Memory bounds exception constructor
 *
 * Constructor for exceptions used for our
 * List  class.
 *
 * @param message The exception message thrown when an error occurs.
 */
ListMemoryBoundsException::ListMemoryBoundsException(const string& message)
{
  this->message = message;
}

/** @brief Memory bounds exception destructor
 *
 * Destructor for exceptions used for our ListMemoryBoundsException
 * class.
 */
ListMemoryBoundsException::~ListMemoryBoundsException() {}

/** @brief Memory bounds exception message
 *
 * Accessor method to access/return message given when an exception occurs.
 *
 * @returns char* Returns a const old style c character array message for
 *   display/use by the process that catches this exception.
 */
const char* ListMemoryBoundsException::what() const throw()
{
  // what expects old style array of characters, so convert to that
  return message.c_str();
}

/**
 * @brief Cause specific instance compilations
 *
 * This is a bit of a kludge, but we can use normal make dependencies
 * and separate compilation by declaring template class List<needed_type>
 * here of any types we are going to be instantianting with the
 * template.
 *
 * https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
 * https://isocpp.org/wiki/faq/templates#separate-template-class-defn-from-decl
 */
template ostream& operator<<<int>(ostream&, const List<int>&);
template class List<int>;

template ostream& operator<<<string>(ostream&, const List<string>&);
template class List<string>;

template <class T>
int List<T>::getSize() const
{
  return size;
}

template <class T>
int List<T>::getAllocationSize() const
{
  return allocationSize;
}

template <class T>
string List<T>::str() const
{
  ostringstream out;
  // stream list information into the output stream
  out << "<list> size: " << size << " allocationSize: " << allocationSize << " [ ";
  // stream the current value sof the list to the output stream
  for (int index = 0; index < size; index++)
  {
    out << values[index];
    // separate the values of the list, last one does not need , separator
    if (index == size - 1)
    {
      out << " ";
    }
    else
    {
      out << ", ";
    }
  }
  out << "]";
  // convert the string stream into a concrete string to return
  return out.str();
}

template <class T>
T& List<T>::operator[](int index)
{
  // first check that the requsted index is legally
  // within the bounds of the current size of our list
  if ((index < 0) or (index >= size))
  {
    ostringstream out;
    out << "Error: illegal bounds access, list size: " << size << " tried to access index address: " << index;
    throw ListMemoryBoundsException(out.str());
  }
  // otherwise it is safe to return the reference to this value
  return values[index];
}

template <class T>
bool List<T>::operator==(const List<T> rhs) const
{
  // first the lists have to be of the same size, or else they
  // cannot be equal
  if (size != rhs.size)
  {
    return false;
  }
  // otherwise, lists are equal if all elements are equal.
  // compare each element, and if we find a pair that is no
  // equal then the answer is false
  for (int index = 0; index < size; index++)
  {
    if (values[index] != rhs.values[index])
    {
      return false;
    }
  }
  // if we get to this point, all values were the same in both
  // lists, so the answer is true, the lists are equal
  return true;
}

template <class T>
ostream& operator<<(ostream& out, const List<T> rhs)
{
  // reuse List str() method to stream to output stream
  out << rhs.str();
  // return the modified output stream as our result
  return out;
}

template <class T>
void List<T>::growListIfNeeded()
{
  // if size is still less than what we have allocated, we still have room
  // to grow at least one or more items in sizes
  if (size < allocationSize)
  {
    return;
  }
  // otherwise size is equal to our allocation, double the size of our allocation
  // to accommodate future growth, or make size 10 initially by default if
  // an empty list is being grown
  if (allocationSize == 0)
  {
    allocationSize = INITIAL_ALLOCATION_SIZE;
  }
  else
  {
    allocationSize = 2 * allocationSize;
  }
  // dynamically allocate a new block of values of the new size
  T* newValues = new T[allocationSize];
  // copy the values from the original memory to this new block of memory
  for (int index = 0; index < size; index++)
  {
    newValues[index] = values[index];
  }
  // we don't need the old block of memory anymore, be good managers of
  // memory and return it to the heap
  delete[] values;
  // now make sure we are using the new block of memory going forward for this
  // list
  values = newValues;
}




template <class T>
List<T>& List<T>::append(T addition)
{
  //first check if list needs to grow
  growListIfNeeded();

  //Increase the size and add addition to the end of the list
  size++;
  operator[](size-1) = addition;
  return *this; 
}

//Essentially a shortcut for using the append method
template <class T>
List<T>& List<T>::operator>>(T addition)
{
  return append(addition);
}


template <class T>
List<T>& List<T>::prepend(T addition)
{
  //Check if list needs to grow
  growListIfNeeded();

  //Increment list and shift all values present up one index
  size++;
  for (int index = size - 1; index > 0; index--)
  {
    operator[](index) = operator[](index - 1);
  }

  //Set the first index value equal to addition
  operator[](0) = addition;
  return *this;
}

//Essentially a shortcut for the prepend method
template <class T>
List<T>& List<T>::operator<<(T addition)
{
  return prepend(addition);
}

template <class T>
List<T>& List<T>::concatenate(const List<T>& list2) const
{
  int concatenatedSize = (this->size) + list2.size;
  T* concatenatedValues = new T[concatenatedSize];
  for (int index = 0; index < this->size; index++)
  {
    concatenatedValues[index] = this->values[index];
  }
  for (int index = 0; index < list2.size; index++)
  {
    concatenatedValues[index + this->size] = list2.values[index];
  }
  List<T>* concatenatedList = new List(concatenatedSize, concatenatedValues);
  delete[] concatenatedValues;
  return *concatenatedList;
}

//Essentially a shortcut for the concatenate method
template <class T>
List<T>& List<T>::operator+(const List<T>& list2) const
{
  return concatenate(list2);
}
