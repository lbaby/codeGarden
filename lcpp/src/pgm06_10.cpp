//
//   This file contains the C++ code from Program 6.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_10.cpp
//
void StackAsLinkedList::Accept (Visitor& visitor) const
{
    ListElement<Object*> const* ptr;

    for (ptr = list.Head ();
	ptr != 0 && !visitor.IsDone (); ptr = ptr->Next ())
    {
	visitor.Visit (*ptr->Datum ());
    }
}
