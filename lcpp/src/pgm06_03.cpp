//
//   This file contains the C++ code from Program 6.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_03.cpp
//
StackAsArray::StackAsArray (unsigned int size) :
    array (size)
    {}

void StackAsArray::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 0; i < count; ++i)
	    delete array [i];
    }
    count = 0;
}

StackAsArray::~StackAsArray ()
    { Purge (); }
