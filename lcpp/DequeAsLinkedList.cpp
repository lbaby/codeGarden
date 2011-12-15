//
//   This file contains the C++ code from Program 6.27 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_27.cpp
//

#include <Object.h>
#include <DequeAsLinkedList.h>

#include <stdexcept>

using std::domain_error;

Object& DequeAsLinkedList::Head () const
    { return QueueAsLinkedList::Head (); }

void DequeAsLinkedList::EnqueueTail (Object& object)
    { QueueAsLinkedList::Enqueue (object); }

Object& DequeAsLinkedList::DequeueHead ()
    { return QueueAsLinkedList::Dequeue (); }
Object& DequeAsLinkedList::Tail () const
{
    if (count == 0)
	throw domain_error ("deque is empty");
    return *list.Last ();
}

void DequeAsLinkedList::EnqueueHead (Object& object)
{
    list.Prepend (&object);
    ++count;
}

Object& DequeAsLinkedList::DequeueTail ()
{
    if (count == 0)
	throw domain_error ("deque is empty");
    Object& result = *list.Last ();
    list.Extract (&result);
    --count;
    return result;
}
