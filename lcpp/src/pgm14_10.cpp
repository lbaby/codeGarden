//
//   This file contains the C++ code from Program 14.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_10.cpp
//
unsigned int Fibonacci (unsigned int n)
{
    if (n == 0 || n == 1)
	return n;
    else
    {
	unsigned int const a = Fibonacci ((n + 1) / 2);
	unsigned int const b = Fibonacci ((n + 1) / 2 - 1);
	if (n % 2 == 0)
	    return a * (a + 2 * b);
	else
	    return a * a + b * b;
    }
}
