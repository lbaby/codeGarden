//
//   This file contains the C++ code from Program 9.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_22.cpp
//
class InfixVisitor : public PrePostVisitor
{
public:
    void PreVisit (Object&)
	{ cout << "("; }
    void Visit (Object& object)
	{ cout << object; }
    void PostVisit (Object&)
	{ cout << ")"; }
};
