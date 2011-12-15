//
//   This file contains the C++ code from Program 6.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_01.cpp
//
class Stack : public virtual Container
{
public:
    virtual Object& Top () const = 0;
    virtual void Push (Object&) = 0;
    virtual Object& Pop () = 0;
};
