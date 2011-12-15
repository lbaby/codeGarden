//
//   This file contains the C++ code from Program 16.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_18.cpp
//
class EarliestTimeVisitor : public Visitor
{
    Graph& graph;
    Array<unsigned int>& earliestTime;
public:
    EarliestTimeVisitor (Graph& g, Array<unsigned int>& e) :
	graph (g), earliestTime (e)
	{}
    void Visit (Object& object)
    {
	Vertex& w = dynamic_cast<Vertex&> (object);
	unsigned int max = earliestTime [0];
	Iterator& p = graph.IncidentEdges (w);
	while (!p.IsDone ()) {
	    WeightedEdge& edge =
		dynamic_cast<WeightedEdge&> (*p);
	    Int& weight =
		dynamic_cast<Int&> (edge.Weight ());
	    Vertex& v = edge.V0 ();
	    unsigned int const t =
		earliestTime [v] + weight;
	    if (t > max)
		max = t;
	    ++p;
	}
	delete &p;
	earliestTime [w] = max;
    }
};
