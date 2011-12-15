//
//   This file contains the C++ code from Program 4.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_02.cpp
//
template <class T>
Array<T>::Array () :
    data (new T [0]),
    base (0),
    length (0)
    {}
