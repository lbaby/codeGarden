//
//   This file contains the C++ code from Program 4.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_20.cpp
//
template <class T>
class Array2D
{
protected:
    unsigned int numberOfRows;
    unsigned int numberOfColumns;
    Array<T> array;
public:
    class Row
    {
	Array2D& array2D;
	unsigned int const row;
    public:
	Row (Array2D& _array2D, unsigned int _row) :
	    array2D (_array2D), row (_row) {}
	T& operator [] (unsigned int column) const
	    { return array2D.Select (row, column); }
    };

    Array2D (unsigned int, unsigned int);
    T& Select (unsigned int, unsigned int);
    Row operator [] (unsigned int);
};
