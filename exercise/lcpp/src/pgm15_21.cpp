//
//   This file contains the C++ code from Program 15.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_21.cpp
//
class RadixSorter : public DistributionSorter<unsigned int>
{
protected:
    static unsigned int const r;
    static unsigned int const R;
    static unsigned int const p;

    Array<unsigned int> count;

    void DoSort (Array<unsigned int>&);
public:
    RadixSorter () : count (R) {}
};
