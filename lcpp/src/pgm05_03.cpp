//
//   This file contains the C++ code from Program 5.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_03.cpp
//
#include <typeinfo>

Object::~Object ()
    {}

bool Object::IsNull () const
    { return false; }

int Object::Compare (Object const& object) const
{
    if (typeid (*this) == typeid (object))
	return CompareTo (object);
    else if (typeid (*this).before (typeid (object)))
	return -1;
    else
	return 1;
}
