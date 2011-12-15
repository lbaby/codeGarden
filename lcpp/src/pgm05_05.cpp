//
//   This file contains the C++ code from Program 5.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_05.cpp
//
NullObject NullObject::instance;

NullObject::NullObject ()
    {}

bool NullObject::IsNull () const
    { return true; }

int NullObject::CompareTo (Object const&) const
    { return 0; } 

HashValue NullObject::Hash () const
    { return 0; }

void NullObject::Put (std::ostream& s) const
    { s << "NullObject"; }

NullObject& NullObject::Instance ()
    { return instance; }
