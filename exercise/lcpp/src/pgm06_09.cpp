//
//   This file contains the C++ code from Program 6.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_09.cpp
//
void StackAsLinkedList::Push (Object& object)
{
    list.Prepend (&object);
    ++count;
}

Object& StackAsLinkedList::Pop ()
{
    if (count == 0)
	throw domain_error ("stack is empty");
    Object& result = *list.First ();
    list.Extract (&result);
    --count;
    return result;
}

Object& StackAsLinkedList::Top () const
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *list.First ();
}
