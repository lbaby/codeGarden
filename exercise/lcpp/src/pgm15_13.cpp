//
//   This file contains the C++ code from Program 15.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_13.cpp
//
template <class T>
void HeapSorter<T>::PercolateDown (
    Array<T>& array, unsigned int length, unsigned int i)
{
    while (i <= length / 2)
    {
	unsigned int child = 2 * i;
	if (child + 1 <= length
		&& array [child + 1] > array [child])
	    child = child + 1;
	if (array [i] >= array [child])
	    break;
	Swap (array [i], array [child]);
	i = child;
    }
}
