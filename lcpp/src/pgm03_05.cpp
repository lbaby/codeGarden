//
//   This file contains the C++ code from Program 3.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm03_05.cpp
//
unsigned int const m = ?;

void BucketSort (unsigned int a [], unsigned int n)
{
    int buckets [m];

    for (unsigned int j = 0; j < m; ++j)
	buckets [j] = 0;
    for (unsigned int i = 0; i < n; ++i)
	++buckets [a [i]];
    for (unsigned int i = 0, j = 0; j < m; ++j)
	for (unsigned int k = buckets [j]; k > 0; --k)
	    a [i++] = j;
}
