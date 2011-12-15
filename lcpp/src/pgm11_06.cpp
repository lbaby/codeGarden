//
//   This file contains the C++ code from Program 11.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_06.cpp
//
Object& BinaryHeap::DequeueMin ()
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    Object& result = *array [1];
    Object& last = *array [count];
    --count;
    unsigned int i = 1;
    while (2 * i < count + 1)
    {
	unsigned int child = 2 * i;
	if (child + 1 < count + 1
	    && *array [child + 1] < *array [child])
	    child += 1;
	if (last <= *array [child])
	    break;
	array [i] = array [child];
	i = child;
    }
    array [i] = &last;
    return result;
}
