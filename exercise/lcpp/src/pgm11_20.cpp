//
//   This file contains the C++ code from Program 11.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_20.cpp
//
Object& BinomialQueue::DequeueMin ()
{
    if (count == 0)
	throw domain_error ("priority queue is empty");

    BinomialTree& minTree = FindMinTree ();
    RemoveTree (minTree);

    BinomialQueue queue;
    while (minTree.Degree () > 0)
    {
	BinomialTree& child = minTree.Subtree (0);

	minTree.DetachSubtree (child);
	queue.AddTree (child);
    }
    Merge (queue);

    Object& result = minTree.Key ();
    minTree.RescindOwnership ();
    delete &minTree;

    return result;
}
