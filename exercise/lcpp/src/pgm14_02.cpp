//
//   This file contains the C++ code from Program 14.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_02.cpp
//
class Solver
{
protected:
    Solution* bestSolution;
    int bestObjective;
    void UpdateBest (Solution const&);
    virtual void DoSolve (Solution const&) = 0;
public:
    virtual Solution& Solve (Solution const&);
};
