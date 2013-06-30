//
//   This file contains the C++ code from Program 6.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_20.cpp
//
void BreadthFirstTraversal (NaryTree& tree)
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.Enqueue (tree);
    while (!queue.IsEmpty ())
    {
	NaryTree& t =
	    dynamic_cast<NaryTree&> (queue.Dequeue ());
	cout << t.Key () << endl;
	for (unsigned int i = 0; i < t.Degree (); ++i)
	{
	    NaryTree& subTree = t.Subtree (i);
	    queue.Enqueue (subTree);
	}
    }
    delete &queue;
}
