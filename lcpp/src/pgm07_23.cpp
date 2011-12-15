//
//   This file contains the C++ code from Program 7.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_23.cpp
//
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
    return count;
}
