//
//   This file contains the C++ code from Program 8.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_09.cpp
//
#ifndef CHAINEDHASHTABLE_H_
#define CHAINEDHASHTABLE_H_

#include <HashTable.h>
#include <Object.h>
#include <Array.h>
#include <LinkedList.h>
#include <Visitor.h>

class ChainedHashTable : public HashTable
{
    Array<LinkedList<Object*> > array;
    int CompareTo(const Object & arg) const ;
public:
    ChainedHashTable (unsigned int);
    ~ChainedHashTable ();
    void Purge ();
    void Insert (Object& object);
    void Withdraw (Object& object);
    Object& Find (Object const& object) const;
    void Accept (Visitor&) const ;
    bool IsMember(const Object&) const;
};

#endif /*CHAINEDHASHTABLE_H_*/
