//
//   This file contains the C++ code from Program 15.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_16.cpp
//
template <class T>
class TwoWayMergeSorter : public MergeSorter<T>
{
protected:
    Array<T>* tempArray;

    void Merge (Array<T>&,
	unsigned int, unsigned int, unsigned int);
    void DoSort (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
public:
    TwoWayMergeSorter () : tempArray (0) {}
};
