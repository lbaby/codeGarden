//
//   This file contains the C++ code from Program 6.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_22.cpp
//
void Deque::Enqueue (Object& object)
    { EnqueueTail (object); }

Object& Deque::Dequeue ()
    { return DequeueHead (); }
