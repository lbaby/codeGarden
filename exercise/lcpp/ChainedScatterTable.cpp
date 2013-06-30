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

#include <ChainedScatterTable.h>
#include <NullObject.h>
#include <stdexcept>

using std::domain_error;
using std::invalid_argument;


ChainedScatterTable::Entry::Entry () :
    object (0),
    next (null)
    {}

ChainedScatterTable::ChainedScatterTable (unsigned int _length) :
    HashTable (SuitablePrime(_length)),
    array (SuitablePrime(_length))
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


void ChainedScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("scatter table is empty");
    unsigned int i = H (object);
    while (i != Entry::null && array [i].object != &object)
	i = array [i].next;
    if (i == Entry::null)
	throw invalid_argument ("object not found");
    for (;;)
    {
	unsigned int j;
	for (j = array [i].next;
	    j != Entry::null; j = array [j].next)
	{
	    unsigned int const h = H (*array [j].object);
	    bool contained = false;
	    for (unsigned int k = array [i].next;
		k != array [j].next && !contained;
		k = array [k].next)
	    {
		if (k == h)
		    contained = true;
	    }
	    if (!contained)
		break;
	}
	if (j == Entry::null)
	    break;
	array [i].object = array [j].object;
	i = j;
    }
    array [i].object = 0;
    array [i].next = Entry::null;
    for (unsigned int j = (i + length - 1U) % length;
	j != i; j = (j + length - 1U) % length)
    {
	if (array [j].next == i)
	{
	    array [j].next = Entry::null;
	    break;
	}
    }
    --count;
}

void ChainedScatterTable::Accept(Visitor& v) const
{
	for(unsigned int i = 0 ; i < length; ++i){
		if(array[i].object  ){
			v.Visit(*array[i].object);
		}
	}
}

bool ChainedScatterTable:: IsMember(const Object& object) const
{
	unsigned int probe = H (object);
    for ( ; probe != Entry::null; probe = array [probe].next)
    {
	if ( &object == array [probe].object)
	    return true;
    }
    
    return false;
}

