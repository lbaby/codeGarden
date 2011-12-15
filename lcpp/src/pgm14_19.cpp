//
//   This file contains the C++ code from Program 14.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_19.cpp
//
double Pi (unsigned int trials)
{
    unsigned int hits = 0;
    for (unsigned int i = 0; i < trials; ++i)
    {
	double const x = RandomNumberGenerator::Next ();
	double const y = RandomNumberGenerator::Next ();
	if (x * x + y * y < 1.0)
	    ++hits;
    }
    return 4.0 * hits / trials;
}
