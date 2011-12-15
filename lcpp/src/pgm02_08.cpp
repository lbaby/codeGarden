//
//   This file contains the C++ code from Program 2.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm02_08.cpp
//
int Power (int x, unsigned int n)
{
    if (n == 0)
	return 1;
    else if (n % 2 == 0) // n is even
	return Power (x * x, n / 2);
    else // n is odd
	return x * Power (x * x, n / 2);
}
