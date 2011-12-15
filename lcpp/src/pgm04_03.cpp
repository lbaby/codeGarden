//
//   This file contains the C++ code from Program 4.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_03.cpp
//
template <class T>
Array<T>::Array (unsigned int n, unsigned int m) :
    data (new T [n]),
    base (m),
    length (n)
    {}
