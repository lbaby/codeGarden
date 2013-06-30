//
//   This file contains the C++ code from Program 15.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_01.cpp
//
template <class T>
class Sorter
{
protected:
    unsigned int n;

    static void Swap (T&, T&);
    virtual void DoSort (Array<T>&) = 0;
public:
    void Sort (Array<T>&);
};
