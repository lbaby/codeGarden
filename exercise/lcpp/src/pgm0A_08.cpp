//
//   This file contains the C++ code from Program A.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_08.cpp
//
class Point
{
    int x;
    int y;
public:
    Point (int, int);
    // ...
};

class GraphicalObject
{
protected:
    Point center;

    GraphicalObject (Point const& p) :
	center (p) {}
public:
    virtual ~GraphicalObject ();
    virtual void Draw () const = 0;
    virtual void Erase () const;
    virtual void MoveTo (Point const&);
};
