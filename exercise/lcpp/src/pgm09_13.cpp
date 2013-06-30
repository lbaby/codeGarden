//
//   This file contains the C++ code from Program 9.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_13.cpp
//
NaryTree::NaryTree (unsigned int _degree) :
    key (0),
    degree (_degree),
    subtree (0)
    {}

NaryTree::NaryTree (unsigned int _degree, Object& _key):
    key (&_key),
    degree (_degree),
    subtree (_degree)
{
    for (unsigned int i = 0; i < degree; ++i)
	subtree [i] = new NaryTree (degree);
}
