//
//   This file contains the C++ code from Program 6.25 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_25.cpp
//
Object& DequeAsArray::Tail () const
{
    if (count == 0)
	throw domain_error ("deque is empty");
    return *array [tail];
}

void DequeAsArray::EnqueueHead (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("deque is full");
    if (head-- == 0)
	head = array.Length () - 1U;
    array [head] = &object;
    ++count;
}


Object& DequeAsArray::DequeueTail ()
{
    if (count == 0)
	throw domain_error ("deque is empty");
    Object& result = *array [tail];
    if (tail-- == 0)
	tail = array.Length () - 1U;
    --count;
    return result;
}
