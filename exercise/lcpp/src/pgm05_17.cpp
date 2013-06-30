//
//   This file contains the C++ code from Program 5.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_17.cpp
//
class Ownership
{
    bool isOwner;
protected:
    Ownership () : isOwner (true)
	{}
    Ownership (Ownership& arg) : isOwner (arg.isOwner)
	{ arg.isOwner = false; }
public:
    void AssertOwnership ()
	{ isOwner = true; }
    void RescindOwnership ()
	{ isOwner = false; }
    bool IsOwner () const
	{ return isOwner; }
};
