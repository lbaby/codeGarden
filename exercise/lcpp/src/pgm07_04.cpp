//
//   This file contains the C++ code from Program 7.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_04.cpp
//
bool ListAsArray::IsMember (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
	if (array [i] == &object)
	    return true;
    return false;
}

Object& ListAsArray::Find (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
	if (*array [i] == object)
	    return *array [i];
    return NullObject::Instance ();
}
