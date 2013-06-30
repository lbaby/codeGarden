//
//   This file contains the C++ code from Program 7.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_05.cpp
//
void ListAsArray::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");
    unsigned int i = 0;
    while (i < count && array [i] != &object)
	++i;
    if (i == count)
	throw invalid_argument ("object not found");

    for ( ; i < count - 1U; ++i)
	array [i] = array [i + 1];
    --count;
}
