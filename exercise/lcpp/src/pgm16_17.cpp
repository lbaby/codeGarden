//
//   This file contains the C++ code from Program 16.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_17.cpp
//
Graph& KruskalsAlgorithm (Graph const& g)
{
    unsigned int const n = g.NumberOfVertices ();

    Graph& result = *new GraphAsLists (n);
    for (Vertex::Number v = 0; v < n; ++v)
	result.AddVertex (*new Vertex (v));

    PriorityQueue& queue = *new BinaryHeap (g.NumberOfEdges ());
    Iterator& p = g.Edges ();
    while (!p.IsDone ()) {
	WeightedEdge& edge =
	    dynamic_cast<WeightedEdge&> (*p);
	Int& weight = dynamic_cast<Int&> (edge.Weight ());
	queue.Enqueue (*new Assoc (weight, edge));
	++p;
    }
    delete &p;

    Partition& partition = *new PartitionAsForest (n);
    while (!queue.IsEmpty () && partition.Count () > 1)
    {
	Assoc& assoc =
	    dynamic_cast<Assoc&> (queue.DequeueMin ());
	Edge& edge = dynamic_cast<Edge&> (assoc.Value ());
	Vertex::Number const v0 = edge.V0 ();
	Vertex::Number const v1 = edge.V1 ();
	Set& s = partition.Find (Set::Element (v0));
	Set& t = partition.Find (Set::Element (v1));
	if (s != t)
	{
	    partition.Join (s, t);
	    result.AddEdge (*new Edge (result[v0], result[v1]));
	}
	delete &assoc;
    }
    delete &partition;
    delete &queue;
    return result;
}
