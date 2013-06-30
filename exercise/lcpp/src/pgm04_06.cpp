//
//   This file contains the C++ code from Program 4.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_06.cpp
//
template <class T>
T const* Array<T>::Data () const
    { return data; }

template <class T>
unsigned int Array<T>::Base () const
    { return base; }

template <class T>
unsigned int Array<T>::Length () const
    { return length; }
