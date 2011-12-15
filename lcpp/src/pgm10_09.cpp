//
//   This file contains the C++ code from Program 10.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_09.cpp
//
void AVLTree::LLRotation ()
{
    if (IsEmpty ())
	throw domain_error ("invalid rotation");
    BinaryTree* const tmp = right;
    right = left;
    left = Right ().left;
    Right ().left = Right ().right;
    Right ().right = tmp;

    Object* const tmpObj = key;
    key = Right ().key;
    Right ().key = tmpObj;

    Right ().AdjustHeight ();
    AdjustHeight ();
}
