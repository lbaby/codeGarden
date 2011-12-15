//
//   This file contains the C++ code from Program 9.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_19.cpp
//
void BinaryTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (visitor.IsDone ())
	return;
    if (!IsEmpty ())
    {
	visitor.PreVisit (*key);
	left->DepthFirstTraversal (visitor);
	visitor.Visit (*key);
	right->DepthFirstTraversal (visitor);
	visitor.PostVisit (*key);
    }
}
