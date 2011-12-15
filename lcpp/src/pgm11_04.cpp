//
//   This file contains the C++ code from Program 11.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_04.cpp
//
void BinaryHeap::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("priority queue is full");
    ++count;
    unsigned int i = count;
    while (i > 1 && *array [i / 2] > object)
    {
	array [i] = array [i / 2];
	i /= 2;
    }
    array [i] = &object;
}
