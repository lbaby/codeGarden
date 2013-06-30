//
//   This file contains the C++ code from Program 16.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_16.cpp
//
Graph& PrimsAlgorithm (Graph const& g, Vertex const& s)
{
    unsigned int const n = g.NumberOfVertices ();
    Array<TableEntry> table (n);
    PriorityQueue& queue = *new BinaryHeap (g.NumberOfEdges ());
    table [s].distance = 0;
    queue.Enqueue (*new Assoc (0, const_cast<Vertex&> (s)));
    while (!queue.IsEmpty ())
    {
	Assoc& assoc =
	    dynamic_cast<Assoc&> (queue.DequeueMin ());
	Vertex& v0 = dynamic_cast<Vertex&> (assoc.Value ());
	if (!table [v0].known)
	{
	    table [v0].known = true;
	    Iterator& p = g.EmanatingEdges (v0);
	    while (!p.IsDone ()) {
		WeightedEdge& edge =
		    dynamic_cast<WeightedEdge&> (*p);
		Vertex& v1 = edge.Mate (v0);
		Int& weight =
		    dynamic_cast<Int&> (edge.Weight ());
		int const d = weight;
		if (!table[v1].known && table[v1].distance > d)
		{
		    table [v1].distance = d;
		    table [v1].predecessor = v0;
		    queue.Enqueue (*new Assoc (d, v1));
		}
		++p;
	    }
	    delete &p;
	}
	delete &assoc;
    }
    delete &queue;

    Graph& result = *new GraphAsLists (n);
    for (Vertex::Number v = 0; v < n; ++v)
	result.AddVertex (*new Vertex (v));

    for (Vertex::Number v = 0; v < n; ++v)
	if (v != s)
	    result.AddEdge (*new Edge (
		result [v], result [table [v].predecessor]));
    return result;
}
