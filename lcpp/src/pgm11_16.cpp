//
//   This file contains the C++ code from Program 11.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_16.cpp
//
BinomialTree& BinomialQueue::FindMinTree () const
{
    ListElement<BinomialTree*> const* ptr;

    BinomialTree* minTree = 0;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
    {
	BinomialTree* tree = ptr->Datum ();
	if (minTree == 0 || tree->Key () < minTree->Key ())
	    minTree = tree;
    }
    return *minTree;
}

Object& BinomialQueue::FindMin () const
{
    if (count == 0)
	throw domain_error ("priority queue is empty");
    return FindMinTree ().Key ();
}
