//
//   This file contains the C++ code from Program 6.24 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_24.cpp
//
Object& DequeAsArray::Head () const
    { return QueueAsArray::Head (); }

void DequeAsArray::EnqueueTail (Object& object)
    { QueueAsArray::Enqueue (object); }

Object& DequeAsArray::DequeueHead ()
    { return QueueAsArray::Dequeue (); }
