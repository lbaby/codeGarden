//
//   This file contains the C++ code from Program 12.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_10.cpp
//
class MultisetAsArray : public Multiset
{
    Array<unsigned int> array;
public:
    MultisetAsArray (unsigned int);
    // ...
};
