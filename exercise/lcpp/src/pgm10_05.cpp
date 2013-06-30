//
//   This file contains the C++ code from Program 10.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_05.cpp
//
void BST::Insert (Object& object)
{
    if (IsEmpty ())
	AttachKey (object);
    else
    {
	int const diff = object.Compare (*key);
	if (diff == 0)
	    throw invalid_argument ("duplicate key");
	if (diff < 0)
	    Left ().Insert (object);
	else
	    Right ().Insert (object);
    }
    Balance ();
}

void BST::AttachKey (Object& object)
{
    if (!IsEmpty ())
	throw domain_error ("invalid operation");
    key = &object;
    left = new BST ();
    right = new BST ();
}

void BST::Balance ()
    {}
