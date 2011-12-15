//
//   This file contains the C++ code from Program 5.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_13.cpp
//
class Iterator
{
public:
    virtual ~Iterator ();
    virtual void Reset () = 0;
    virtual bool IsDone () const = 0;
    virtual Object& operator * () const = 0;
    virtual void operator ++ () = 0;
};
