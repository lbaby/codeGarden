//
//   This file contains the C++ code from Program 14.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_08.cpp
//
void DepthFirstBranchAndBoundSolver::DoSolve (
    Solution const& solution)
{
    if (solution.IsComplete ())
	UpdateBest (solution);
    else
    {
	Iterator& i = solution.Successors ();
	while (!i.IsDone ()) {
	    Solution& successor = dynamic_cast<Solution&> (*i);
	    if (successor.IsFeasible () &&
		    successor.Bound () < bestObjective)
		DoSolve (successor);
	    delete &successor;
	    ++i;
	}
	delete &i;
    }
}
