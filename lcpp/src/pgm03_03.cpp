//
//   This file contains the C++ code from Program 3.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm03_03.cpp
//
unsigned int Fibonacci (unsigned int n)
{
    int previous = -1;
    int result = 1;
    for (unsigned int i = 0; i <= n; ++i)
    {
	int const sum = result + previous;
	previous = result;
	result = sum;
    }
    return result;
}
