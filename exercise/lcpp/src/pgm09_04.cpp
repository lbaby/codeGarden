//
//   This file contains the C++ code from Program 9.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_04.cpp
//
void Tree::BreadthFirstTraversal (Visitor& visitor) const
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();

    if (!IsEmpty ())
	queue.Enqueue (const_cast<Tree&> (*this));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
	Tree const& head =
	    dynamic_cast<Tree const &> (queue.Dequeue ());

	visitor.Visit (head.Key ());
	for (unsigned int i = 0; i < head.Degree (); ++i)
	{
	    Tree& child = head.Subtree (i);
	    if (!child.IsEmpty ())
		queue.Enqueue (child);
	}
    }
    delete &queue;
}
