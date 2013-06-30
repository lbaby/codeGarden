//
//   This file contains the C++ code from Program 7.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_13.cpp
//
void ListAsLinkedList::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");
    linkedList.Extract (&object);
    --count;
}
