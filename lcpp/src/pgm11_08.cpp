//
//   This file contains the C++ code from Program 11.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_08.cpp
//
void LeftistHeap::Merge (MergeablePriorityQueue& queue)
{
    LeftistHeap& arg = dynamic_cast<LeftistHeap&> (queue);
    if (IsEmpty ())
	SwapContents (arg);
    else if (!arg.IsEmpty ())
    {
	if (*key > *arg.key)
	    SwapContents (arg);
	Right ().Merge (arg);
	if (Left ().nullPathLength < Right ().nullPathLength)
	    Swap (left, right);
	nullPathLength = 1 + Min (Left ().nullPathLength,
	    Right ().nullPathLength);
    }
}
