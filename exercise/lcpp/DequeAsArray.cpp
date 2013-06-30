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

#include <DequeAsArray.h>
#include <stdexcept>
#include <Visitor.h>

#include <stdio.h>

using std::domain_error;

Object& DequeAsArray::Head () const
    { return QueueAsArray::Head (); }

void DequeAsArray::EnqueueTail (Object& object)
    { QueueAsArray::Enqueue (object); }

Object& DequeAsArray::DequeueHead ()
    { return QueueAsArray::Dequeue (); }

   
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


void DequeAsArray::Accept(Visitor &visitor) const
{
	/*
	for (int i = head; 
	i < count  && ! visitor.IsDone() ;
	++i)
	{
		fprintf(stderr, "i");
		visitor.Visit(* array[i % array.Length() ]);
	}*/
	
	QueueAsArray::Accept(visitor);
}
