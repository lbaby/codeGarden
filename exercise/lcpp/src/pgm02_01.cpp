//
//   This file contains the C++ code from Program 2.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm02_01.cpp
//
unsigned int Sum (unsigned int n)
{
    unsigned int result = 0;
    for (unsigned int i = 1; i <= n; ++i)
	result += i;
    return result;
}
