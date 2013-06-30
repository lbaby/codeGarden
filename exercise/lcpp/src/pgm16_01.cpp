//
//   This file contains the C++ code from Program 16.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_01.cpp
//
class Vertex : public Object
{
public:
    typedef unsigned int Number;
protected:
    Number number;
public:
    Vertex (Number);
    virtual operator Number () const;
    // ...
};
