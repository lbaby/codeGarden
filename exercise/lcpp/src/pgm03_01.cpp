//
//   This file contains the C++ code from Program 3.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm03_01.cpp
//
int Horner (int a [], unsigned int n, int x)
{
    int result = a [n];
    for (int i = n - 1; i >= 0; --i)
	result = result * x + a [i];
    return result;
}
