//
//   This file contains the C++ code from Program 7.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_11.cpp
//
ListAsLinkedList::ListAsLinkedList () :
    linkedList ()
    {}

void ListAsLinkedList::Insert (Object& object)
{
    linkedList.Append (&object);
    ++count;
}

Object& ListAsLinkedList::operator [] (unsigned int offset) const
{
    if (offset >= count)
	throw out_of_range ("invalid offset");

    unsigned int i = 0;
    ListElement<Object*> const* ptr =
	linkedList.Head ();
    while (i < offset && ptr != 0)
    {
	ptr = ptr->Next ();
	++i;
    }
    if (ptr == 0)
	throw logic_error ("should never happen");
    return *ptr->Datum ();
}
