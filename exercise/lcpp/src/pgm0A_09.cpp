//
//   This file contains the C++ code from Program A.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_09.cpp
//
void GraphicalObject::Erase () const
{
    SetPenColour (backgroundColour);
    Draw ();
    SetPenColour (foregroundColour);
}

void GraphicalObject::MoveTo (Point const& p)
{
    Erase ();
    center = p;
    Draw ();
}
