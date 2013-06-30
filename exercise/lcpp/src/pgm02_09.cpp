//
//   This file contains the C++ code from Program 2.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm02_09.cpp
//
int Power (int, unsigned int);

int GeometricSeriesSum (int x, unsigned int n)
{
    return (Power (x, n + 1) - 1) / (x - 1);
}
