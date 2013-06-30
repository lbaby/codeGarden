//
//   This file contains the C++ code from Program 13.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_01.cpp
//
class StoragePool
{
public:
    virtual ~StoragePool ();
    virtual void* Acquire (size_t) = 0;
    virtual void Release (void*) = 0;
};
