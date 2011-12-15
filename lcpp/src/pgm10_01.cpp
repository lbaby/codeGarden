//
//   This file contains the C++ code from Program 10.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_01.cpp
//
class SearchTree :
    public virtual Tree, public virtual SearchableContainer
{
public:
    virtual Object& FindMin () const = 0;
    virtual Object& FindMax () const = 0;
};
