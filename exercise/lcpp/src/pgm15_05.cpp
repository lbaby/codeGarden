//
//   This file contains the C++ code from Program 15.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm15_05.cpp
//
template <class T>
class BinaryInsertionSorter : public InsertionSorter<T>
{
protected:
    void DoSort (Array<T>&);
};

template <class T>
void BinaryInsertionSorter<T>::DoSort (Array<T>& array)
{
    for (unsigned int i = 1; i < n; ++i)
    {
	T const& tmp = array [i];
	unsigned int left = 0;
	unsigned int right = i;
	while (left < right)
	{
	    unsigned int const middle = (left + right) / 2;
	    if (tmp >= array [middle])
		left = middle + 1;
	    else
		right = middle;
	}
	for (unsigned int j = i; j > left; --j)
	    Swap (array [j - 1U], array [j]);
    }
}
