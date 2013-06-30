//
//   This file contains the C++ code from Program 8.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_19.cpp
//
unsigned int OpenScatterTable::C (unsigned int i) const
    { return i; }

unsigned int OpenScatterTable::FindUnoccupied (
    Object const& object) const
{
    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < count + 1; ++i)
    {
	unsigned int const probe = (hash + C (i)) % length;
	if (array [probe].state != Entry::occupied)
	    return probe;
    }
    return length;
}

void OpenScatterTable::Insert (Object& object)
{
    if (count == length)
	throw domain_error ("scatter table is full");
    unsigned int const offset = FindUnoccupied (object);
    array [offset].state = Entry::occupied;
    array [offset].object = &object;
    ++count;
}
