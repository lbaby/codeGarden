//
//   This file contains the C++ code from Program 10.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_06.cpp
//
void BST::Withdraw (Object& object)
{
    if (IsEmpty ())
	throw invalid_argument ("object not found");
    int const diff = object.Compare (*key);
    if (diff == 0)
    {
	if (!Left ().IsEmpty ())
	{
	    Object& max = Left ().FindMax ();
	    key = &max;
	    Left ().Withdraw (max);
	}
	else if (!Right ().IsEmpty ())
	{
	    Object& min = Right ().FindMin ();
	    key = &min;
	    Right ().Withdraw (min);
	}
	else
	    DetachKey ();
    }
    else if (diff < 0)
	Left ().Withdraw (object);
    else
	Right ().Withdraw (object);
    Balance ();
}

Object& BST::DetachKey ()
{
    if (!IsLeaf ())
	throw domain_error ("invalid operation");
    Object& result = *key;
    delete left;
    delete right;
    key = 0;
    left = 0;
    right = 0;
    return result;
}
