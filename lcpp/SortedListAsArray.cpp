//
//   This file contains the C++ code from Program 7.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_22.cpp
//

#include <Object.h>
#include <SortedListAsArray.h>
#include <NullObject.h>

#ifdef DPRINT
	#include <iostream>
#endif


#include <stdexcept>


using std::domain_error;
using std::invalid_argument;

void SortedListAsArray::Insert (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("list is full");
    unsigned int i = count;
    while (i > 0 && *array [i - 1U] > object)
    {
	array [i] = array [i - 1U];
	--i;
    }
    array [i] = &object;
    ++count;
}


unsigned int SortedListAsArray::FindOffset (
    Object const& object) const
{
    int left = 0;
    int right = count - 1;

    while (left <= right)
    {
	int const middle = (left + right) / 2;

	if (object > *array [middle])
	left = middle + 1;
	else if (object < *array [middle])
	    
	     	right = middle - 1;
	else
	    return middle;
    }
    
    #ifdef DPRINT
    std::cout << "Obj  in find offset: " << object << std::endl;
    #endif
    return count;
}


Object& SortedListAsArray::Find (Object const& object) const
{
    unsigned int const offset = FindOffset (object);

    if (offset < count)
	return *array [offset];
    else
	return NullObject::Instance ();
}

Position& SortedListAsArray::FindPosition (
    Object const& object) const
{
    Pos& result = *new Pos (*this);
    result.offset = FindOffset (object);
    return result;
}


void SortedListAsArray::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");

    unsigned int const offset = FindOffset (object);

    if (offset == count)
	throw invalid_argument ("object not found");

    for (unsigned int i = offset; i < count - 1U; ++i)
	array [i] = array [i + 1];
    --count;
}
