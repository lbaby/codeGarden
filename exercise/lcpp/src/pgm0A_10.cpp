//
//   This file contains the C++ code from Program A.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_10.cpp
//
class Circle : public GraphicalObject
{
    int radius;
public:
    Circle (Point const& p, int r) :
	GraphicalObject (p), radius (r) {}

    void Draw () const;
};

class Rectangle : public GraphicalObject
{
    int height;
    int width;
public:
    Rectangle (Point const& p, int ht, int wid) :
	GraphicalObject (p), height (ht), width (wid) {}

    void Draw () const;
};

class Square : public Rectangle
{
public:
    Square (Point const& p, int wid) :
	Rectangle (p, wid, wid) {}
};
