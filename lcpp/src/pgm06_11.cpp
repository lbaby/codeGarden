//
//   This file contains the C++ code from Program 6.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_11.cpp
//
StackAsLinkedList::Iter::Iter (
    StackAsLinkedList const& _stack) :
    stack (_stack)
    { Reset (); }

bool StackAsLinkedList::Iter::IsDone () const
    { return position == 0; }

Object& StackAsLinkedList::Iter::operator * () const
{
    if (position != 0)
	return *position->Datum ();
    else
	return NullObject::Instance ();
}

void StackAsLinkedList::Iter::operator ++ ()
{
    if (position != 0)
	position = position->Next ();
}

void StackAsLinkedList::Iter::Reset ()
    { position = stack.list.Head (); }
