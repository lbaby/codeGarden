//
//   This file contains the C++ code from Program 6.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_16.cpp
//
Object& QueueAsArray::Head () const
{
    if (count == 0)
	throw domain_error ("queue is empty");
    return *array [head];
}

void QueueAsArray::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("queue is full");
    if (++tail == array.Length ())
	tail = 0;
    array [tail] = &object;
    ++count;
}

Object& QueueAsArray::Dequeue ()
{
    if (count == 0)
	throw domain_error ("queue is empty");
    Object& result = *array [head];
    if (++head == array.Length ())
	head = 0;
    --count;
    return result;
}
