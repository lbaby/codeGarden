//
//   This file contains the C++ code from Program 9.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_20.cpp
//
int BinaryTree::CompareTo (Object const& object) const
{
    BinaryTree const& arg = 
	dynamic_cast<BinaryTree const&> (object);
    if (IsEmpty ())
	return arg.IsEmpty () ? 0 : -1;
    else if (arg.IsEmpty ())
	return 1;
    else
    {
	int result = Key ().Compare (arg.Key ());
	if (result == 0)
	    result = Left ().CompareTo (arg.Left ());
	if (result == 0)
	    result = Right ().CompareTo (arg.Right ());
	return result;
    }
}
