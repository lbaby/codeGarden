//
//   This file contains the C++ code from Program 4.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_21.cpp
//
template <class T>
Array2D<T>::Array2D (unsigned int m, unsigned int n) :
    numberOfRows (m),
    numberOfColumns (n),
    array (m * n)
    {}

template <class T>
T& Array2D<T>::Select (unsigned int i, unsigned int j)
{
    if (i >= numberOfRows)
	throw out_of_range ("invalid row");
    if (j >= numberOfColumns)
	throw out_of_range ("invalid column");
    return array [i * numberOfColumns + j];
}

template <class T>
Array2D<T>::Row Array2D<T>::operator [] (unsigned int row)
    { return Row (*this, row); }
