//
//   This file contains the C++ code from Program 8.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_08.cpp
//
HashTable::HashTable (unsigned int _length) :
    length (_length)
    {}

unsigned int HashTable::H (Object const& object) const
    { return object.Hash () % length; }
