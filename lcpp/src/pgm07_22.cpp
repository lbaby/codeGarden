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
