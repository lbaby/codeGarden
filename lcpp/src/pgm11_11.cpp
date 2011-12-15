//
//   This file contains the C++ code from Program 11.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_11.cpp
//
Object& LeftistHeap::DequeueMin ()
{
    if (IsEmpty ())
	throw domain_error ("priority queue is empty");
    Object& result = *key;
    LeftistHeap& oldLeft = Left ();
    LeftistHeap& oldRight = Right ();
    key = 0;
    left = 0;
    right = 0;
    SwapContents (oldLeft);
    delete &oldLeft;
    Merge (oldRight);
    delete &oldRight;
    return result;
}
