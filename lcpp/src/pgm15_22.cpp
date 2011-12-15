//
//   This file contains the C++ code from Program 15.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_22.cpp
//
unsigned int const RadixSorter::r = 8;
unsigned int const RadixSorter::R = 1 << r;
unsigned int const RadixSorter::p =
    (bitsizeof (unsigned int) + r - 1U) / r;

void RadixSorter::DoSort (Array<unsigned int>& array)
{
    Array<unsigned int> tempArray (n);
    for (unsigned int i = 0; i < p; ++i)
    {
	for (unsigned int j = 0; j < R; ++j)
	    count [j] = 0;
	for (unsigned int k = 0; k < n; ++k)
	{
	    ++count [(array [k] >> (r * i)) & (R - 1U)];
	    tempArray [k] = array [k];
	}
	unsigned int pos = 0;
	for (unsigned int j = 0; j < R; ++j)
	{
	    unsigned int const tmp = count [j];
	    count [j] = pos;
	    pos += tmp;
	}
	for (unsigned int k = 0; k < n; ++k)
	{
	    unsigned int j =
		(tempArray [k] >> (r * i)) & (R - 1U);
	    array [count [j]++] = tempArray [k];
	}
    }
}
