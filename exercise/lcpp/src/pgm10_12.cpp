//
//   This file contains the C++ code from Program 10.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_12.cpp
//
void AVLTree::AttachKey (Object& object)
{
    if (!IsEmpty ())
	throw domain_error ("invalid operation");
    key = &object;
    left = new AVLTree ();
    right = new AVLTree ();
    height = 0;
}

Object& AVLTree::DetachKey ()
{
    height = -1;
    return BST::DetachKey ();
}
