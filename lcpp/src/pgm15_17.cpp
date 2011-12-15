//
//   This file contains the C++ code from Program 15.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_17.cpp
//
template <class T>
void TwoWayMergeSorter<T>::Merge (Array<T>& array,
    unsigned int left, unsigned int middle, unsigned int right)
{
    unsigned int i = left;
    unsigned int j = left;
    unsigned int k = middle + 1;
    while (j <= middle && k <= right)
    {
	if (array [j] <= array [k])
	    (*tempArray) [i++] = array [j++];
	else
	    (*tempArray) [i++] = array [k++];
    }
    while (j <= middle)
	(*tempArray) [i++] = array [j++];
    while (k <= right)
	(*tempArray) [i++] = array [k++];
    for (i = left; i <= right; ++i)
	array [i] = (*tempArray) [i];
}
