//
//   This file contains the C++ code from Program 11.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_02.cpp
//



#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <Array.h>
#include <PriorityQueue.h>
#include <Visitor.h>

class BinaryHeap : public PriorityQueue
{
    Array<Object*> array;
    int CompareTo(const Object&) const;
public:
    BinaryHeap (unsigned int);
    ~BinaryHeap ();
    void Enqueue (Object& object);
    void Purge ();
    Object& FindMin () const;
    void Accept(Visitor&) const;
    Object& DequeueMin ();
};

#endif /*BINARYHEAP_H_*/
