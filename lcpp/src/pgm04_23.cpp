//
//   This file contains the C++ code from Program 4.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_23.cpp
//
template <class T>
Matrix<T> Matrix<T>::operator * (Matrix<T> const& arg) const
{
    if (numberOfColumns != arg.numberOfRows)
	throw invalid_argument ("incompatible matrices");
    Matrix<T> result (numberOfRows, arg.numberOfColumns);
    for (unsigned int i = 0; i < numberOfRows; ++i)
    {
	for (unsigned int j = 0; j < arg.numberOfColumns; ++j)
	{
	    T sum = 0;
	    for (unsigned int k = 0; k < numberOfColumns; ++k)
		sum += (*this) [i][k] * arg [k][j];
	    result [i][j] = sum;
	}
    }
    return result;
}
