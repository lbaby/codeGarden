//
//   This file contains the C++ code from Program 8.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_07.cpp
//
class HashTable : public virtual SearchableContainer
{
protected:
    unsigned int length;
public:
    HashTable (unsigned int);
    virtual unsigned int H (Object const&) const;
};
