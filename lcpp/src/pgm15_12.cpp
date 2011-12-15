//
//   This file contains the C++ code from Program 15.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_12.cpp
//
template <class T>
class HeapSorter : public SelectionSorter<T>
{
protected:
    void BuildHeap (Array<T>&);
    void PercolateDown (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
};
