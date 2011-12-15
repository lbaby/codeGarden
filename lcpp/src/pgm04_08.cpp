//
//   This file contains the C++ code from Program 4.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_08.cpp
//
template <class T>
void Array<T>::SetBase (unsigned int newBase)
    { base = newBase; }

template <class T>
void Array<T>::SetLength (unsigned int newLength)
{
    T* const newData = new T [newLength];
    unsigned int const min =
	length < newLength ? length : newLength;
    for (unsigned int i = 0; i < min; ++i)
	newData [i] = data [i];
    delete [] data;
    data = newData;
    length = newLength;
}
