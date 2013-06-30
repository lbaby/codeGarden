//
//   This file contains the C++ code from Program 16.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_06.cpp
//
class WeightedVertex : public Vertex
{
    Object* weight;
public:
    WeightedVertex (Vertex::Number, Object&);
    virtual Object& Weight () const;
    // ...
};
    
class WeightedEdge : public Edge
{
    Object* weight;
public:
    WeightedEdge (Vertex&, Vertex&, Object&);
    virtual Object& Weight () const;
    // ...
};
