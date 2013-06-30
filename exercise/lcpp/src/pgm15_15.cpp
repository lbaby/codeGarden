//
//   This file contains the C++ code from Program 15.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_15.cpp
//
template <class T>
void HeapSorter<T>::DoSort (Array<T>& array)
{
    array.SetBase (1);
    BuildHeap (array);
    for (unsigned int i = n; i >= 2; --i)
    {
	Swap (array [i], array [1]);
	PercolateDown (array, i - 1U, 1);
    }
}
