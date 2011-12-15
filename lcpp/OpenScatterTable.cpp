

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

#include <OpenScatterTable.h>
#include <NullObject.h>
#include <stdexcept>

using std::invalid_argument;
using std::domain_error;

OpenScatterTable::Entry::Entry () :
    state (empty),
    object (0)
    {}

OpenScatterTable::OpenScatterTable (unsigned int _length) :
    HashTable (SuitablePrime(_length)),
    array (SuitablePrime(_length))
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

unsigned int OpenScatterTable::C (unsigned int i, Object const &object) const
    { return  i*  ( 1+ H( object)% ( length -1) )  ; }

unsigned int OpenScatterTable::FindUnoccupied (
    Object const& object) const
{
    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < count + 1; ++i)
    {
	unsigned int const probe = (hash + C (i, object)) % length;
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

unsigned int OpenScatterTable::FindMatch (
    Object const& object) const
{
    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < length; ++i)
    {
	unsigned int const probe = (hash + C (i, object)) % length;
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


void OpenScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("scatter table is empty");
    unsigned int i = FindInstance (object);
    if (i == length)
	throw invalid_argument ("object not found");
    for (;;)
    {
	unsigned int j;
	for (j = (i + C(1, object) ) % length;
	    array [j].state == Entry::occupied;
	    j = (j + 1) % length)
	{
	    unsigned int const h = H (*array [j].object);
	    if ((h <= i && i < j) || (i < j && j < h) ||
		(j < h && h <= i))
		break;
	}
	if (array [j].state == Entry::empty)
	    break;
	array [i] = array [j];
	i = j;
    }
    array [i].state = Entry::empty;
    array [i].object = 0;
    --count;
}

int OpenScatterTable::CompareTo(Object const & arg) const
{
	OpenScatterTable const &ost = 
	dynamic_cast< OpenScatterTable const &>(arg);
	
	return (int)(count - ost.count);
}

void OpenScatterTable::Accept(Visitor& v) const
{
	for(unsigned int i = 0 ; i < length ; ++i){
		if(array[i].state == Entry:: occupied){
			v.Visit(*array[i].object);
		}
	}
}


 bool OpenScatterTable::IsMember(const Object& object ) const
 {
 	    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < length; ++i)
    {
	unsigned int const probe = (hash + C (i, object)) % length;
	if (array [probe].state == Entry::empty)
	    break;
	if (array [probe].state == Entry::occupied
	    &&  &object == array [probe].object)
	    return true;
    }
    return false;
 	
 }
 
 unsigned int OpenScatterTable::FindInstance (
    Object const& object) const
{
    unsigned int const hash = H (object);
    for (unsigned int i = 0; i < length; ++i)
    {
	unsigned int const probe = (hash + C (i, object)) % length;
	if (array [probe].state == Entry::empty)
	    break;
	if (array [probe].state == Entry::occupied
	    &&  &object == array [probe].object)
	    return probe;
    }
    return length;
}


