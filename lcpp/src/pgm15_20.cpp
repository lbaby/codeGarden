//
//   This file contains the C++ code from Program 15.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_20.cpp
//
void BucketSorter::DoSort (Array<unsigned int>& array)
{
    for (unsigned int i = 0; i < m; ++i)
	count [i] = 0;
    for (unsigned int j = 0; j < n; ++j)
	++count [array [j]];
    for (unsigned int i = 0, j = 0; i < m; ++i)
	for ( ; count [i] > 0; --count [i])
	    array [j++] = i;
}
