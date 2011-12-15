//
//   This file contains the C++ code from Program 8.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_20.cpp
//
unsigned int OpenScatterTable::FindMatch (
    Object const& object) const
{
    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < length; ++i)
    {
	unsigned int const probe = (hash + C (i)) % length;
	if (array [probe].state == Entry::empty)
	    break;
	if (array [probe].state == Entry::occupied
	    && object == *array [probe].object)
	    return probe;
    }
    return length;
}

Object& OpenScatterTable::Find (Object const& object) const
{
    unsigned int const offset = FindMatch (object);
    if (offset < length)
	return *array [offset].object;
    else
	return NullObject::Instance ();
}
