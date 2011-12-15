//
//   This file contains the C++ code from Program 7.27 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_27.cpp
//
void SortedListAsLinkedList::Insert (Object& object)
{
    ListElement<Object*> const* prevPtr = 0;
    ListElement<Object*> const* ptr =
	linkedList.Head ();
    while (ptr != 0 && *ptr->Datum () < object)
    {
	prevPtr = ptr;
	ptr = ptr->Next ();
    }
    if (prevPtr == 0)
	linkedList.Prepend (&object);
    else
	linkedList.InsertAfter (prevPtr, &object);
    ++count;
}
