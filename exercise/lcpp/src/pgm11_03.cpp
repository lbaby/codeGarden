//
//   This file contains the C++ code from Program 11.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_03.cpp
//
BinaryHeap::BinaryHeap (unsigned int length) :
    array (length, 1)
    {}

void BinaryHeap::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 1; i < count + 1; ++i)
	    delete array [i];
    }
    count = 0;
}

BinaryHeap::~BinaryHeap ()
    { Purge (); }
