//
//   This file contains the C++ code from Program 6.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_06.cpp
//
StackAsArray::Iter::Iter (StackAsArray const& _stack) :
    stack (_stack)
    { Reset (); }

bool StackAsArray::Iter::IsDone () const
    { return position >= stack.count; }

Object& StackAsArray::Iter::operator * () const
{
    if (position < stack.count)
	return *stack.array [position];
    else
	return NullObject::Instance ();
}

void StackAsArray::Iter::operator ++ ()
{
    if (position < stack.count)
	++position;
}

void StackAsArray::Iter::Reset ()
    { position = 0; }
