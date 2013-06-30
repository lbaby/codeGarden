//
//   This file contains the C++ code from Program 14.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_13.cpp
//
unsigned int Binom (unsigned int n, unsigned int m)
{
    Array<unsigned int> b (n + 1);
    b [0] = 1;
    for (unsigned int i = 1; i <= n; ++i)
    {
	b [i] = 1;
	for (unsigned int j = i - 1U; j > 0; --j)
	    b [j] += b [j - 1U];
    }
    return b [m];
}
