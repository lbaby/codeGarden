//
//   This file contains the C++ code from Program 16.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_11.cpp
//
bool Digraph::IsConnected () const
{
    for (Vertex::Number v = 0; v < numberOfVertices; ++v)
    {
	CountingVisitor visitor;
	DepthFirstTraversal (
	    PreOrder (visitor), SelectVertex (v));
	if (visitor.Count () != numberOfVertices)
	    return false;
    }
    return true;
}
