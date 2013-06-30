//
//   This file contains the C++ code from Program 4.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_04.cpp
//
template <class T>
Array<T>::Array (Array<T> const& array) :
    data (new T [array.length]),
    base (array.base),
    length (array.length)
{
    for (unsigned int i = 0; i < length; ++i)
	data [i] = array.data [i];
}
