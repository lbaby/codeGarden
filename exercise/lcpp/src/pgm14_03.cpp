//
//   This file contains the C++ code from Program 14.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_03.cpp
//
Solution& Solver::Solve (Solution const& initial)
{
    bestSolution = 0;
    bestObjective = numeric_limits<int>::max ();
    DoSolve (initial);
    if (bestSolution == 0)
	throw domain_error ("no feasible solution found");
    return *bestSolution;
}

void Solver::UpdateBest (Solution const& solution)
{
    if (solution.IsFeasible() &&
	solution.Objective () < bestObjective)
    {
	delete bestSolution;
	bestSolution = &(solution.Clone ());
	bestObjective = solution.Objective ();
    }
}
