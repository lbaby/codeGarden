//
//   This file contains the C++ code from Program 15.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_02.cpp
//
template <class T>
void Sorter<T>::Swap (T& x, T& y)
{
    T const tmp = x;
    x = y;
    y = tmp;
}

template <class T>
void Sorter<T>::Sort (Array<T>& array)
{
    n = array.Length ();
    if (n > 0)
    {
	unsigned int const tmp = array.Base ();
	array.SetBase (0);
	DoSort (array);
	array.SetBase (tmp);
    }
}
