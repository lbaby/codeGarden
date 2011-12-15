//
//   This file contains the C++ code from Program 15.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_04.cpp
//
template <class T>
class StraightInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void StraightInsertionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = 1; i < n; ++i)
	for (unsigned int j = i;
		j > 0 && array [j - 1U] > array [j]; --j)
	    Swap (array [j], array [j - 1U]);
}
