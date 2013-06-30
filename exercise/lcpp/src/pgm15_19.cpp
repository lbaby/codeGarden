//
//   This file contains the C++ code from Program 15.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_19.cpp
//
class BucketSorter : public DistributionSorter<unsigned int>
{
protected:
    unsigned int const m;
    Array<unsigned int> count;

    void DoSort (Array<unsigned int>&);
public:
    BucketSorter (unsigned int _m) : m (_m), count (_m) {}
};
