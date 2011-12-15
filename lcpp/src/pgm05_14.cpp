//
//   This file contains the C++ code from Program 5.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_14.cpp
//
class NullIterator : public Iterator
{
public:
    NullIterator ();
    void Reset ();
    bool IsDone () const;
    Object& operator * () const;
    void operator ++ ();
};
