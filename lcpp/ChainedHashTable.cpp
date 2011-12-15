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

#include <ChainedHashTable.h>
#include <NullObject.h>

ChainedHashTable::ChainedHashTable (unsigned int _length) :
    HashTable (SuitablePrime(_length)),
    array (SuitablePrime(_length))
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
    
    
    void ChainedHashTable::Insert (Object& object)
{
    array [H (object)].Append (&object);
    ++count;
}

void ChainedHashTable::Withdraw (Object& object)
{
    array [H (object)].Extract (&object);
    --count;
}


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


int ChainedHashTable::CompareTo(const Object & arg) const 
{
	ChainedHashTable const & ch = 
	dynamic_cast<ChainedHashTable const &>(arg);
	return (int)(count - ch.count);
}


   void ChainedHashTable::Accept (Visitor& v)  const  
{
    for (unsigned int i = 0; i < length; ++i)
    {
	
	    ListElement<Object*> const* ptr;

	    for (ptr = array [i].Head ();
		    ptr != 0; ptr = ptr->Next ())
		v.Visit( * ptr->Datum());
    }

}

bool ChainedHashTable::IsMember(const Object& o) const
{
	    for (unsigned int i = 0; i < length; ++i)
    {
	
	    ListElement<Object*> const* ptr;

	    for (ptr = array [H(o) ].Head ();
		    ptr != 0; ptr = ptr->Next ()){
		    	if (ptr->Datum() == &o ){
		    		return true;
		    	}
		    }
    }
    
    return false;
	
}


