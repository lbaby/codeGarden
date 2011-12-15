//
//   This file contains the C++ code from Program 16.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_04.cpp
//
class GraphAsMatrix : public virtual Graph
{
protected:
    Array<Vertex*> vertices;
    Array2D<Edge*> adjacencyMatrix;
public:
    GraphAsMatrix (unsigned int);
    // ...
};
