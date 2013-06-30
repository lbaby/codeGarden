//
//   This file contains the C++ code from Program 2.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm02_04.cpp
//
unsigned int FindMaximum (unsigned int a [], unsigned int n)
{
    unsigned int result = a [0];
    for (unsigned int i = 1; i < n; ++i)
	if (a [i] > result)
	    result = a [i];
    return result;
}
