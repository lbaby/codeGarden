//
//   This file contains the C++ code from Program 3.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm03_04.cpp
//
unsigned int Fibonacci (unsigned int n)
{
    if (n == 0 || n == 1)
	return n;
    else
	return Fibonacci (n - 1U) + Fibonacci (n - 2U);
}
