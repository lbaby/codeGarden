//
//   This file contains the C++ code from Program 15.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_09.cpp
//
template <class T>
void QuickSorter<T>::DoSort (Array<T>& array)
{
    DoSort (array, 0, n - 1U);
    StraightInsertionSorter<T> s;
    s.Sort (array);
}
