//
//   This file contains the C++ code from Program 14.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_09.cpp
//
template <class T>
unsigned int BinarySearch (
    Array<T> const& array, T const& target,
    unsigned int i, unsigned int n)
{
    if (n == 0)
	throw invalid_argument ("empty array");
    if (n == 1)
    {
	if (array [i] == target)
	    return i;
	throw domain_error ("target not found");
    }
    else
    {
	unsigned int const j = i + n / 2;
	if (array [j] <= target)
	    return BinarySearch (array, target, j, n - n / 2);
	else
	    return BinarySearch (array, target, i, n / 2);
    }
}
