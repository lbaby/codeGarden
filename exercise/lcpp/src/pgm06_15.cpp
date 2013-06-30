//
//   This file contains the C++ code from Program 6.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_15.cpp
//
QueueAsArray::QueueAsArray (unsigned int size) :
    array (size),
    head (0),
    tail (size - 1U)
    {}

void QueueAsArray::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 0; i < count; ++i)
	{
	    delete array [head];
	    if (++head == array.Length ())
		head = 0;
	}
    }
    count = 0;
}

QueueAsArray::~QueueAsArray ()
    { Purge (); }
