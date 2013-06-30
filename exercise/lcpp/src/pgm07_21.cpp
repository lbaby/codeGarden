//
//   This file contains the C++ code from Program 7.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_21.cpp
//
class SortedListAsArray :
    public virtual SortedList, public virtual ListAsArray
{
    unsigned int FindOffset (Object const&) const;
public:
    SortedListAsArray (unsigned int);
    // ...
};
