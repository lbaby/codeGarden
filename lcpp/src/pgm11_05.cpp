//
//   This file contains the C++ code from Program 11.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_05.cpp
//
Object& BinaryHeap::FindMin () const
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    return *array [1];
}
