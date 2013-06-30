//
//   This file contains the C++ code from Program 10.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_16.cpp
//
unsigned int MWayTree::FindIndex (Object const& object) const
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    if (object < *key [1])
	return 0;
    unsigned int left = 1;
    unsigned int right = numberOfKeys;
    while (left < right)
    {
	int const middle = (left + right + 1) / 2;
	if (object >= *key [middle])
	    left = middle;
	else
	    right = middle - 1U;
    }
    return left;
}

Object& MWayTree::Find (Object const& object) const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
	return *key [index];
    else
	return subtree [index]->Find (object);
}
