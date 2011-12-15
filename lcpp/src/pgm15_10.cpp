//
//   This file contains the C++ code from Program 15.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_10.cpp
//
template <class T>
class MedianOfThreeQuickSorter : public QuickSorter<T>
{
protected:
    unsigned int SelectPivot (
	Array<T>&, unsigned int, unsigned int);
};

template <class T>
unsigned int MedianOfThreeQuickSorter<T>::SelectPivot (
    Array<T>& array, unsigned int left, unsigned int right)
{
    unsigned int middle = (left + right) / 2;
    if (array [left] > array [middle])
	Swap (left, middle);
    if (array [left] > array [right])
	Swap (left, right);
    if (array [middle] > array [right])
	Swap (middle, right);
    return middle;
}
