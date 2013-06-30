//
//   This file contains the C++ code from Program 10.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_15.cpp
//
Object& MWayTree::Find (Object const& object) const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    unsigned int i = numberOfKeys;
    while (i > 0)
    {
	int const diff = object.Compare (*key [i]);
	if (diff == 0)
	    return *key [i];
	if (diff > 0)
	    break;
	--i;
    }
    return subtree [i]->Find (object);
}
