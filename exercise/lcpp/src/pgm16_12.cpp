//
//   This file contains the C++ code from Program 16.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_12.cpp
//
bool Digraph::IsCyclic () const
{
    CountingVisitor visitor;
    TopologicalOrderTraversal (visitor);
    return visitor.Count () != numberOfVertices;
}
