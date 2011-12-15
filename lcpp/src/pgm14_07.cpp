//
//   This file contains the C++ code from Program 14.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_07.cpp
//
void BreadthFirstSolver::DoSolve (Solution const& initial)
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.Enqueue (initial.Clone ());
    while (!queue.IsEmpty ())
    {
	Solution& solution =
	    dynamic_cast<Solution&> (queue.Dequeue ());
	if (solution.IsComplete ())
	    UpdateBest (solution);
	else
	{
	    Iterator& i = solution.Successors ();
	    while (!i.IsDone ()) {
		Solution& succ = dynamic_cast<Solution&> (*i);
		queue.Enqueue (succ);
		++i;
	    }
	    delete &i;
	}
	delete &solution;
    }
    delete &queue;
}
