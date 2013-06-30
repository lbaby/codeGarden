//
//   This file contains the C++ code from Program 6.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_18.cpp
//

#include <QueueAsLinkedList.h>
#include <Object.h>
#include <Visitor.h>


QueueAsLinkedList::QueueAsLinkedList () :
    list ()
    {}

void QueueAsLinkedList::Purge ()
{
    if (IsOwner ())
    {
	ListElement<Object*> const* ptr;

	for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	    delete ptr->Datum ();
    }
    list.Purge ();
    count = 0;
}

QueueAsLinkedList::~QueueAsLinkedList ()
    { Purge (); }
   
   
   Object& QueueAsLinkedList::Head () const
{
    if (count == 0)
	throw domain_error ("queue is empty");
    return *list.First ();
}

void QueueAsLinkedList::Enqueue (Object& object)
{
    list.Append (&object);
    ++count;
}

Object& QueueAsLinkedList::Dequeue ()
{
    if (count == 0)
	throw domain_error ("queue is empty");
    Object& result = *list.First ();
    list.Extract (&result);
    --count;
    return result;
}

void QueueAsLinkedList::Accept (Visitor& visitor) const
{
	ListElement<Object*> const* ptr;

	for (ptr = list.Head ();  ptr && ( !visitor.IsDone() ) ; ptr = ptr->Next ()){
		visitor.Visit( *ptr->Datum());
	}
}

