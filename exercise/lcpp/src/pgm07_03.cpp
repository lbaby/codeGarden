//
//   This file contains the C++ code from Program 7.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_03.cpp
//
ListAsArray::ListAsArray (unsigned int size) :
    array (size)
    {}

void ListAsArray::Insert (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("list is full");
    array [count] = &object;
    ++count;
}

Object& ListAsArray::operator [] (unsigned int offset) const
{
    if (offset >= count)
	throw out_of_range ("invalid offset");
    return *array [offset];
}
