//
//   This file contains the C++ code from Program 16.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_10.cpp
//
class CountingVisitor : public Visitor
{
    unsigned int count;
public:
    CountingVisitor () : count (0)
	{}
    void Visit (Object&)
	{ ++count; }
    unsigned int Count () const
	{ return count; }
};

bool Graph::IsConnected () const
{
    CountingVisitor visitor;
    DepthFirstTraversal (PreOrder (visitor), SelectVertex (0));
    return visitor.Count () == numberOfVertices;
}
