//
//   This file contains the C++ code from Program 12.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_16.cpp
//
class Partition : public Set
{
public:
    Partition (unsigned int n) : Set (n) {}

    virtual Set& Find (Object const&) const = 0;
    virtual void Join (Set&, Set&) = 0;
};
