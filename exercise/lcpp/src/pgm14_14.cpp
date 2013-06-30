//
//   This file contains the C++ code from Program 14.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_14.cpp
//
void Typeset (Array<unsigned int> const& l,
    unsigned int D, unsigned int s)
{
    unsigned int const n = l.Length ();
    Array2D<unsigned int> L (n, n);
    for (unsigned int i = 0; i < n; ++i)
    {
	L [i][i] = l [i];
	for (unsigned int j = i + 1; j < n; ++j)
	    L [i][j] = L [i][j - 1U] + l [j];
    }
    Array2D<unsigned int> P (n, n);
    for (unsigned int i = 0; i < n; ++i)
	for (unsigned int j = i; j < n; ++j)
	{
	    if (L [i][j] < D)
		P [i][j] = abs (D - L [i][j] - (j - i) * s);
	    else
		P [i][j] = numeric_limits<unsigned int>::max ();
	}
    Array2D<unsigned int> C (n, n);
    for (unsigned int j = 0; j < n; ++j)
    {
	C [j][j] = P [j][j];
	for (int i = j - 1; i >= 0; --i)
	{
	    unsigned int min = P [i][j];
	    for (unsigned int k = i; k < j; ++k)
	    {
		unsigned int const tmp = P [i][k] + C [k + 1][j];
		if (tmp < min)
		    min = tmp;
	    }
	    C [i][j] = min;
	}
    }
}
