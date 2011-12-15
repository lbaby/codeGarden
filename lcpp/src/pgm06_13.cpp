//
//   This file contains the C++ code from Program 6.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_13.cpp
//
class Queue : public virtual Container
{
public:
    virtual Object& Head () const = 0;
    virtual void Enqueue (Object&) = 0;
    virtual Object& Dequeue () = 0;
};
