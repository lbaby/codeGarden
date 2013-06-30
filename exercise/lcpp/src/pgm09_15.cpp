//
//   This file contains the C++ code from Program 9.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_15.cpp
//
NaryTree& NaryTree::Subtree (unsigned int i) const
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    return *subtree [i];
}

void NaryTree::AttachSubtree (unsigned int i, NaryTree& t)
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    if (!subtree [i]->IsEmpty ())
	throw domain_error ("non-empty subtree present");
    delete subtree [i];
    subtree [i] = &t;
}

NaryTree& NaryTree::DetachSubtree (unsigned int i)
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    NaryTree& result = *subtree [i];
    subtree [i] = new NaryTree (degree);
    return result;
}
