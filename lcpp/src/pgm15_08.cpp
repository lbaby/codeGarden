//
//   This file contains the C++ code from Program 15.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_08.cpp
//
template <class T>
void QuickSorter<T>::DoSort (
    Array<T>& array, unsigned int left, unsigned int right)
{
    if (right - left + 1 > cutOff)
    {
	unsigned int const p = SelectPivot (array, left, right);
	Swap (array [p], array [right]);
	T& pivot = array [right];
	unsigned int i = left;
	unsigned int j = right - 1U;
	for (;;)
	{
	    while (i < j && array [i] < pivot) ++i;
	    while (i < j && array [j] > pivot) --j;
	    if (i >= j) break;
	    Swap (array [i++], array [j--]);
	}
	if (array [i] > pivot)
	    Swap (array [i], pivot);
	if (left < i)
	    DoSort (array, left, i - 1U);
	if (right > i)
	    DoSort (array, i + 1, right);
    }
}
