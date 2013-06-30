//
//   This file contains the C++ code from Program 8.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_02.cpp
//
HashValue Hash (double d)
{
    if (d == 0)
	return 0;
    else
    {
	int exponent;
	double mantissa = std::frexp (d, &exponent);
	return (2 * fabs (mantissa) - 1) * ~0U;
    }
}
