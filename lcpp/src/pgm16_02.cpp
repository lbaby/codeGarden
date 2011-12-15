//
//   This file contains the C++ code from Program 16.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_02.cpp
//
class Edge : public Object
{
protected:
    Vertex& v0;
    Vertex& v1;
public:
    Edge (Vertex&, Vertex&);
    virtual Vertex& V0 () const;
    virtual Vertex& V1 () const;
    virtual Vertex& Mate (Vertex const&) const;
    // ...
};
