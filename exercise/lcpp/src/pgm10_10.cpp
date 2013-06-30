//
//   This file contains the C++ code from Program 10.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_10.cpp
//
void AVLTree::LRRotation ()
{
    if (IsEmpty ())
	throw domain_error ("invalid rotation");
    Left ().RRRotation ();
    LLRotation ();
}
