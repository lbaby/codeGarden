//
//   This file contains the C++ code from Program 16.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_15.cpp
//
Digraph& FloydsAlgorithm (Digraph const& g)
{
    using numeric_limits<unsigned int>::max;

    unsigned int const n = g.NumberOfVertices ();
    Array2D<unsigned int> distance (n, n);
    for (Vertex::Number v = 0; v < n; ++v)
	for (Vertex::Number w = 0; w < n; ++w)
	    distance [v][w] = max ();
    Iterator& p = g.Edges ();
    while (!p.IsDone ())
    {
	WeightedEdge& edge = 
	    dynamic_cast<WeightedEdge&> (*p);
	Int& weight = dynamic_cast<Int&> (edge.Weight ());
	distance [edge.V0 ()][edge.V1 ()] = weight;
	++p;
    }
    delete &p;

    for (Vertex::Number i = 0; i < n; ++i)
	for (Vertex::Number v = 0; v < n; ++v)
	    for (Vertex::Number w = 0; w < n; ++w)
		if (distance [v][i] != max () &&
		    distance [i][w] != max ())
		{
		    int const d =
			distance [v][i] + distance [i][w];
		    if (distance [v][w] > d)
			distance [v][w] = d;
		}

    Digraph& result = *new DigraphAsMatrix (n);
    for (Vertex::Number v = 0; v < n; ++v)
	result.AddVertex (*new Vertex (v));
    for (Vertex::Number v = 0; v < n; ++v)
	for (Vertex::Number w = 0; w < n; ++w)
	    if (distance [v][w] != max ())
		result.AddEdge (*new WeightedEdge (
		    result [v], result [w],
		    *new Int (distance [v][w])));
    return result;
}
