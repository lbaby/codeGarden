//
//   This file contains the C++ code from Program 6.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_05.cpp
//
void StackAsArray::Accept (Visitor& visitor) const
{
    for (unsigned int i = 0;
	i < count && !visitor.IsDone (); ++i)
    {
	visitor.Visit (*array [i]);
    }
}
