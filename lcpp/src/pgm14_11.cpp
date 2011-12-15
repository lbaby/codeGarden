//
//   This file contains the C++ code from Program 14.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_11.cpp
//
template <class T>
void MergeSort (Array<T>& array, unsigned int i, unsigned int n)
{
    if (n > 1)
    {
	MergeSort (array, i, n / 2);
	MergeSort (array, i + n / 2, n - n / 2);
	Merge (array, i, n / 2, n - n / 2);
    }
}
