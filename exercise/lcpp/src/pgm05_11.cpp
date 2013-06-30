//
//   This file contains the C++ code from Program 5.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_11.cpp
//
class Visitor
{
public:
    virtual void Visit (Object&) = 0;
    virtual bool IsDone () const
	{ return false; }
};
