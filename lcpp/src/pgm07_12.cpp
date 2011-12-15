//
//   This file contains the C++ code from Program 7.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_12.cpp
//
bool ListAsLinkedList::IsMember (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = linkedList.Head (); ptr != 0; ptr = ptr->Next ())
	if (ptr->Datum () == &object)
	    return true;
    return false;
}

Object& ListAsLinkedList::Find (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = linkedList.Head (); ptr != 0; ptr = ptr->Next ())
	if (*ptr->Datum () == object)
	    return *ptr->Datum ();
    return NullObject::Instance ();
}
