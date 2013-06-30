//
//   This file contains the C++ code from Program 2.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm02_03.cpp
//
unsigned int Factorial (unsigned int n)
{
    if (n == 0)
	return 1;
    else
	return n * Factorial (n - 1);
}
