//
//   This file contains the C++ code from Program 5.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_15.cpp
//
NullIterator::NullIterator ()
    {}

void NullIterator::Reset ()
    {}

bool NullIterator::IsDone () const
    { return true; }

Object& NullIterator::operator * () const
    { return NullObject::Instance (); }

void NullIterator::operator ++ ()
    {}
