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
Object& DequeAsLinkedList::Head () const
    { return QueueAsLinkedList::Head (); }

void DequeAsLinkedList::EnqueueTail (Object& object)
    { QueueAsLinkedList::Enqueue (object); }

Object& DequeAsLinkedList::DequeueHead ()
    { return QueueAsLinkedList::Dequeue (); }
