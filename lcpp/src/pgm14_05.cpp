//
//   This file contains the C++ code from Program 14.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_05.cpp
//
void DepthFirstSolver::DoSolve (Solution const& solution)
{
    if (solution.IsComplete ())
	UpdateBest (solution);
    else
    {
	Iterator& i = solution.Successors ();
	while (!i.IsDone ()) {
	    Solution& successor = dynamic_cast<Solution&> (*i);
	    DoSolve (successor);
	    delete &successor;
	    ++i;
	}
	delete &i;
    }
}
