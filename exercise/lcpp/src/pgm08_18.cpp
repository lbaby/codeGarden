//
//   This file contains the C++ code from Program 8.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_18.cpp
//
OpenScatterTable::Entry::Entry () :
    state (empty),
    object (0)
    {}

OpenScatterTable::OpenScatterTable (unsigned int _length) :
    HashTable (_length),
    array (_length)
    {}

void OpenScatterTable::Purge ()
{
    for (unsigned int i = 0; i < length; ++i)
    {
	if (array [i].state == Entry::occupied)
	{
	    if (IsOwner ())
		delete array [i].object;
	    array [i] = Entry ();
	}
    }
    count = 0;
}

OpenScatterTable::~OpenScatterTable ()
    { Purge (); }
