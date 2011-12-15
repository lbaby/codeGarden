//
//   This file contains the C++ code from Program 9.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_02.cpp
//
void Tree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (visitor.IsDone ())
	return;
    if (!IsEmpty ())
    {
	visitor.PreVisit (Key ());
	for (unsigned int i = 0; i < Degree (); ++i)
	    Subtree (i).DepthFirstTraversal (visitor);
	visitor.PostVisit (Key ());
    }
}
