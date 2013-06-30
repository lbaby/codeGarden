//
//   This file contains the C++ code from Program 15.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_14.cpp
//
template <class T>
void HeapSorter<T>::BuildHeap (Array<T>& array)
{
    for (unsigned int i = n / 2; i > 0; --i)
	PercolateDown (array, n, i);
}
