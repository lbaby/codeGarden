//
//   This file contains the C++ code from Program 15.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_07.cpp
//
template <class T>
class QuickSorter : public ExchangeSorter<T>
{
protected:
    static unsigned int const cutOff;

    virtual unsigned int SelectPivot (
	Array<T>&, unsigned int, unsigned int) = 0;
    void DoSort (Array<T>&, unsigned int, unsigned int);
    void DoSort (Array<T>&);
};
