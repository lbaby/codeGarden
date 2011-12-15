//
//   This file contains the C++ code from Program 4.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_22.cpp
//
template <class T>
class Matrix : public Array2D<T>
{
public:
    Matrix (unsigned int, unsigned int);
    Matrix operator * (Matrix const&) const;
    Matrix operator + (Matrix const&) const;
};
