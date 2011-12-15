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

#include <LeftistHeap.h>
#include <stdexcept>
#include <ToolKits.h>



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


void LeftistHeap::Enqueue (Object& object)
{
    LeftistHeap heap (object);
    Merge (heap);
}


Object& LeftistHeap::FindMin () const
{
    if (IsEmpty ())
	throw std::domain_error ("priority queue is empty");
    return *key;
}



Object& LeftistHeap::DequeueMin ()
{
    if (IsEmpty ())
	throw std::domain_error ("priority queue is empty");
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


LeftistHeap::~LeftistHeap()
{
	if(IsEmpty()){
		return ;
	}else{
		delete  left;
		delete right;
	}
}
