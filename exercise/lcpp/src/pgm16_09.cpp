//
//   This file contains the C++ code from Program 16.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_09.cpp
//
void Digraph::TopologicalOrderTraversal (Visitor& visitor) const
{
    Array<unsigned int> inDegree (numberOfVertices);
    for (Vertex::Number v = 0; v < numberOfVertices; ++v)
	inDegree [v] = 0;
    Iterator& p = Edges ();
    while (!p.IsDone ()) {
	Edge& edge = dynamic_cast<Edge&> (*p);
	++inDegree [edge.V1 ()];
	++p;
    }
    delete &p;

    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();
    for (Vertex::Number v = 0; v < numberOfVertices; ++v)
	if (inDegree [v] == 0)
	    queue.Enqueue (SelectVertex (v));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
	Vertex& vertex =
	    dynamic_cast<Vertex&> (queue.Dequeue ());
	visitor.Visit (vertex);
	Iterator& q = EmanatingEdges (vertex);
	while (!q.IsDone ()) {
	    Edge& edge = dynamic_cast<Edge&> (*q);
	    Vertex& to = edge.V1 ();
	    if (--inDegree [to] == 0)
		queue.Enqueue (to);
	    ++q;
	}
	delete &q;
    }
    delete &queue;
}
