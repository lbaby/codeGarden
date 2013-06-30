//
//   This file contains the C++ code from Program 10.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_13.cpp
//
class MWayTree : public SearchTree
{
protected:
    unsigned int const m;
    unsigned int numberOfKeys;
    Array<Object*> key;
    Array<MWayTree*> subtree;

    unsigned int FindIndex (Object const&) const;
public:
    MWayTree (unsigned int);
    ~MWayTree ();

    Object& Key (unsigned int) const;
    MWayTree& Subtree (unsigned int) const;
    // ...
};
