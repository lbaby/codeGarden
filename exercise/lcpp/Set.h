#ifndef SET_H_
#define SET_H_
//
//   This file contains the C++ code from Program 12.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_01.cpp
//

#include <Wrapper.h>
#include <SearchableContainer.h>

class Set : public virtual SearchableContainer
{
protected:
    unsigned int universeSize;

public:
    Set (unsigned int n) : universeSize (n) {}

    typedef Wrapper<unsigned int> Element;
};

#endif /*SET_H_*/
