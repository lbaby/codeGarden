//
//   This file contains the C++ code from Program 6.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_08.cpp
//
StackAsLinkedList::StackAsLinkedList () :
    list ()
    {}

void StackAsLinkedList::Purge ()
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

StackAsLinkedList::~StackAsLinkedList ()
    { Purge (); }
