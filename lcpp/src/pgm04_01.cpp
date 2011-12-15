//
//   This file contains the C++ code from Program 4.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_01.cpp
//
template <class T>
class Array
{
protected:
    T* data;
    unsigned int base;
    unsigned int length;
public:
    Array ();
    Array (unsigned int, unsigned int = 0);
    ~Array ();

    Array (Array const&);
    Array& operator = (Array const&);

    T const& operator [] (unsigned int) const;
    T& operator [] (unsigned int);

    T const* Data () const;
    unsigned int Base () const;
    unsigned int Length () const;

    void SetBase (unsigned int);
    void SetLength (unsigned int);
};
