//
//   This file contains the C++ code from Program 15.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_06.cpp
//
template <class T>
class BubbleSorter : public ExchangeSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void BubbleSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = n; i > 1; --i)
	for (unsigned int j = 0; j < i - 1U; ++j)
	    if (array [j] > array [j + 1])
		Swap (array [j], array [j + 1]);
}
