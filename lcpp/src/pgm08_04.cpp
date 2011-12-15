//
//   This file contains the C++ code from Program 8.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_04.cpp
//
template <class T>
HashValue Wrapper<T>::Hash () const
    { return ::Hash (datum); }
