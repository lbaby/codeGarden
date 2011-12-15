//
//   This file contains the C++ code from Program 8.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_10.cpp
//
ChainedHashTable::ChainedHashTable (unsigned int _length) :
    HashTable (_length),
    array (_length)
    {}

void ChainedHashTable::Purge ()
{
    for (unsigned int i = 0; i < length; ++i)
    {
	if (IsOwner ())
	{
	    ListElement<Object*> const* ptr;

	    for (ptr = array [i].Head ();
		    ptr != 0; ptr = ptr->Next ())
		delete ptr->Datum ();
	}
	array [i].Purge ();
    }
    count = 0;
}

ChainedHashTable::~ChainedHashTable ()
    { Purge (); }
