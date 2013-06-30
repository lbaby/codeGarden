//
//   This file contains the C++ code from Program 16.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_07.cpp
//
void Graph::DepthFirstTraversal (
    PrePostVisitor& visitor, Vertex const& start) const
{
    Array<bool> visited (numberOfVertices);
    for (Vertex::Number v = 0; v < numberOfVertices; ++v)
	visited [v] = false;
    DepthFirstTraversal (
	visitor, const_cast<Vertex&> (start), visited);
}

void Graph::DepthFirstTraversal (PrePostVisitor& visitor,
    Vertex& vertex, Array<bool>& visited) const
{
    if (visitor.IsDone ())
	return;
    visitor.PreVisit (vertex);
    visited [vertex] = true;
    Iterator& p = EmanatingEdges (vertex);
    while (!p.IsDone ()) {
	Edge& edge = dynamic_cast<Edge&> (*p);
	Vertex& to = edge.Mate (vertex);
	if (!visited [to])
	    DepthFirstTraversal (visitor, to, visited);
	++p;
    }
    delete &p;
    visitor.PostVisit (vertex);
}
