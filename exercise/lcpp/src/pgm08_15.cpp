//
//   This file contains the C++ code from Program 8.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_15.cpp
//
void ChainedScatterTable::Insert (Object& object)
{
    if (count == length)
	throw domain_error ("scatter table is full");
    unsigned int probe = H (object);
    if (array [probe].object != 0)
    {
	while (array [probe].next != Entry::null)
	    probe = array [probe].next;
	unsigned int const tail = probe;
	probe = (probe + 1) % length;
	while (array [probe].object != 0)
	    probe = (probe + 1) % length;
	array [tail].next = probe;
    }
    array [probe].object = &object;
    array [probe].next = Entry::null;
    ++count;
}

Object& ChainedScatterTable::Find (Object const& object) const
{
    unsigned int probe = H (object);
    if (array[probe].object == 0)
	return NullObject::Instance ();
    for ( ; probe != Entry::null; probe = array [probe].next)
    {
	if (object == *array [probe].object)
	    return *array [probe].object;
    }
    return NullObject::Instance ();
}
