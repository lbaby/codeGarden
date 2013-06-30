//
//   This file contains the C++ code from Program 7.24 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_24.cpp
//
Object& SortedListAsArray::Find (Object const& object) const
{
    unsigned int const offset = FindOffset (object);

    if (offset < count)
	return *array [offset];
    else
	return NullObject::Instance ();
}

Position& SortedListAsArray::FindPosition (
    Object const& object) const
{
    Pos& result = *new Pos (*this);
    result.offset = FindOffset (object);
    return result;
}
