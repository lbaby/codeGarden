//
//   This file contains the C++ code from Program 8.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_14.cpp
//
ChainedScatterTable::Entry::Entry () :
    object (0),
    next (null)
    {}

ChainedScatterTable::ChainedScatterTable (unsigned int _length) :
    HashTable (_length),
    array (_length)
    {}

void ChainedScatterTable::Purge ()
{
    for (unsigned int i = 0; i < length; ++i)
    {
	if (array [i].object != 0)
	{
	    if (IsOwner ())
		delete array [i].object;
	    array [i] = Entry ();
	}
    }
    count = 0;
}

ChainedScatterTable::~ChainedScatterTable ()
    { Purge (); }
