#ifndef BINOMIALQUEUE_H_
#define BINOMIALQUEUE_H_
//
//   This file contains the C++ code from Program 11.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_14.cpp
//

#include <PriorityQueue.h>
#include <LinkedList.h>
#include <BinomialTree.h>


class BinomialQueue : public  MergeablePriorityQueue
{
    LinkedList<BinomialTree*> list;
 int CompareTo(const Object&) const;
 
    BinomialTree& FindMinTree () const;
    void AddTree (BinomialTree&);
    void RemoveTree (BinomialTree&);

    static BinomialTree* Sum (
	BinomialTree*, BinomialTree*, BinomialTree*);
    static BinomialTree* Carry (
	BinomialTree*, BinomialTree*, BinomialTree*);
public:
    BinomialQueue ():list()
    {}
    ~BinomialQueue ()
    {
    	Purge();
    }
    
    virtual void Purge();
    virtual void Accept(Visitor&) const;
    Object& FindMin () const;
    void Merge (MergeablePriorityQueue& queue);
    void Enqueue (Object& object);
    Object& DequeueMin ();
 
};

#endif /*BINOMIALQUEUE_H_*/
