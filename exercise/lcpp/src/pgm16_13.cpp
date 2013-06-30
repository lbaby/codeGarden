//
//   This file contains the C++ code from Program 16.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm16_13.cpp
//
struct TableEntry
{
    bool known;
    int distance;
    Vertex::Number predecessor;

    TableEntry () : known (false),
	distance (numeric_limits<int>::max ()) {}
};

class Assoc : public Association
{
    Int priority;
public:
    Assoc (int p, Object& object) :
	Association (priority, object), priority (p)
	{ RescindOwnership (); }
};
