//
//   This file contains the C++ code from Program 14.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_12.cpp
//
unsigned int Fibonacci (unsigned int n, unsigned int k)
{
    if (n < k - 1U)
	return 0;
    else if (n == k - 1U)
	return 1;
    else
    {
	Array<unsigned int> f (n + 1);
	for (unsigned int i = 0; i < k - 1U; ++i)
	    f [i] = 0;
	f [k - 1U] = 1;
	for (unsigned int i = k; i <= n; ++i)
	{
	    unsigned int sum = 0;
	    for (unsigned int j = 1; j <= k; ++j)
		sum += f [i - j];
	    f [i] = sum;
	}
	return f [n];
    }
}
