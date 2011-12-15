//
//   This file contains the C++ code from Program 15.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_11.cpp
//
template <class T>
class StraightSelectionSorter : public SelectionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void StraightSelectionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = n; i > 1; --i)
    {
	unsigned int max = 0;
	for (unsigned int j = 1; j < i; ++j)
	    if (array [j] > array [max])
		max = j;
	Swap (array [i - 1U], array [max]);
    }
}
