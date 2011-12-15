//
//   This file contains the C++ code from Program 10.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_14.cpp
//
void MWayTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (!IsEmpty ())
    {
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	    visitor.PreVisit (*key [i]);
	subtree [0]->DepthFirstTraversal (visitor);
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	{
	    visitor.Visit (*key [i]);
	    subtree [i]->DepthFirstTraversal (visitor);
	}
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	    visitor.PostVisit (*key [i]);
    }
}
