//
//   This file contains the C++ code from Program 8.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_12.cpp
//
Object& ChainedHashTable::Find (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = array [H (object)].Head ();
	ptr != 0; ptr = ptr->Next())
    {
	if (object == *ptr->Datum ())
	    return *ptr->Datum ();
    }
    return NullObject::Instance ();
}
