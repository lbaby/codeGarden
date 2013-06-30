//
//   This file contains the C++ code from Program 6.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_19.cpp
//
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
