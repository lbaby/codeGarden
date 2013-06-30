//
//   This file contains the C++ code from Program 16.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_08.cpp
//
void Graph::BreadthFirstTraversal (
    Visitor& visitor, Vertex const& start) const
{
    Array<bool> enqueued (numberOfVertices);
    for (Vertex::Number v = 0; v < numberOfVertices; ++v)
	enqueued [v] = false;

    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();

    enqueued [start] = true;
    queue.Enqueue (const_cast<Vertex&> (start));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
	Vertex& vertex =
	    dynamic_cast<Vertex&> (queue.Dequeue ());
	visitor.Visit (vertex);
	Iterator& p = EmanatingEdges (vertex);
	while (!p.IsDone ()) {
	    Edge& edge = dynamic_cast<Edge&> (*p);
	    Vertex& to = edge.Mate (vertex);
	    if (!enqueued [to])
	    {
		enqueued [to] = true;
		queue.Enqueue (to);
	    }
	    ++p;
	}
	delete &p;
    }
    delete &queue;
}
