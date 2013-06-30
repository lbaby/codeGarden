//
//   This file contains the C++ code from Program 7.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_15.cpp
//
Position& ListAsLinkedList::FindPosition (
    Object const& object) const
{
    ListElement<Object*> const* ptr =
	linkedList.Head ();
    while (ptr != 0 && *ptr->Datum () != object)
	ptr = ptr->Next ();
    return *new Pos (*this, ptr);
}

Object& ListAsLinkedList::operator [] (
    Position const& arg) const
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");
    return *position.element->Datum ();
}
