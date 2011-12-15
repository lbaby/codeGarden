//
//   This file contains the C++ code from Program 4.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_07.cpp
//
template <class T>
T const& Array<T>::operator [] (unsigned int position) const
{
    unsigned int const offset = position - base;
    if (offset >= length)
	throw out_of_range ("invalid position");
    return data [offset];
}

template <class T>
T& Array<T>::operator [] (unsigned int position)
{
    unsigned int const offset = position - base;
    if (offset >= length)
	throw out_of_range ("invalid position");
    return data [offset];
}
