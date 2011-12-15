//
//   This file contains the C++ code from Program 15.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_18.cpp
//
template <class T>
void TwoWayMergeSorter<T>::DoSort (Array<T>& array)
{
    tempArray = new Array<T> (n);
    DoSort (array, 0, n - 1U);
    delete tempArray;
    tempArray = 0;
}

template <class T>
void TwoWayMergeSorter<T>::DoSort (Array<T>& array,
    unsigned int left, unsigned int right)
{
    if (left < right)
    {
	unsigned int const middle = (left + right) / 2;
	DoSort (array, left, middle);
	DoSort (array, middle + 1, right);
	Merge (array, left, middle, right);
    }
}
