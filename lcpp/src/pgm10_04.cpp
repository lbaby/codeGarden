//
//   This file contains the C++ code from Program 10.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_04.cpp
//
Object& BST::Find (Object const& object) const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    int const diff = object.Compare (*key);
    if (diff == 0)
	return *key;
    else if (diff < 0)
	return Left ().Find (object);
    else
	return Right ().Find (object);
}

Object& BST::FindMin () const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    else if (Left ().IsEmpty ())
	return *key;
    else
	return Left ().FindMin();
}
