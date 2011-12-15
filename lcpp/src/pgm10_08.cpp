//
//   This file contains the C++ code from Program 10.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_08.cpp
//
AVLTree::AVLTree () :
    BST (),
    height (-1)
    {}

int AVLTree::Height () const
    { return height; }

void AVLTree::AdjustHeight ()
{
    if (IsEmpty ())
	height = -1;
    else
	height = Max (left->Height (), right->Height ()) + 1;
}

int AVLTree::BalanceFactor () const
{
    if (IsEmpty ())
	return 0;
    else
	return left->Height () - right->Height ();
}
