//
//   This file contains the C++ code from Program 7.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_06.cpp
//
class ListAsArray::Pos : public Position
{
protected:
    ListAsArray const& list;
    unsigned int offset;
public:
    // ...
    friend class ListAsArray;
    friend class SortedListAsArray;
};
