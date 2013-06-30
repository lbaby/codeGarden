//
//   This file contains the C++ code from Program 16.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_19.cpp
//
Digraph& CriticalPathAnalysis (Digraph& g)
{
    unsigned int const n = g.NumberOfVertices ();

    Array<unsigned int> earliestTime (n);
    earliestTime [0] = 0;
    g.TopologicalOrderTraversal (
	EarliestTimeVisitor (g, earliestTime));

    Array<unsigned int> latestTime (n);
    latestTime [n - 1U] = earliestTime [n - 1U];
    g.DepthFirstTraversal (PostOrder (
	LatestTimeVisitor (g, latestTime)), g[0]);

    DigraphAsLists slackGraph (n);
    for (Vertex::Number v = 0; v < n; ++v)
	slackGraph.AddVertex (*new Vertex (v));
    Iterator& p = g.Edges ();
    while (!p.IsDone ()) {
	WeightedEdge& edge =
	    dynamic_cast<WeightedEdge&> (*p);
	Int& weight =
	    dynamic_cast<Int&> (edge.Weight ());
	Vertex& v0 = edge.V0 ();
	Vertex& v1 = edge.V1 ();
	unsigned int const slack =
	    latestTime [v1] - earliestTime [v0] - weight;
	slackGraph.AddEdge (*new WeightedEdge (
	    slackGraph [v0], slackGraph [v1], *new Int(slack)));
	++p;
    }
    delete &p;

    return DijkstrasAlgorithm (slackGraph, slackGraph [0]);
}
