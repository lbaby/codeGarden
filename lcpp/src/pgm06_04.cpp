//
//   This file contains the C++ code from Program 6.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_04.cpp
//
void StackAsArray::Push (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("stack is full");
    array [count++] = &object;
}

Object& StackAsArray::Pop ()
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *array [--count];
}

Object& StackAsArray::Top () const
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *array [count - 1U];
}
