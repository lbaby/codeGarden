//
//   This file contains the C++ code from Program 7.25 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_25.cpp
//
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
