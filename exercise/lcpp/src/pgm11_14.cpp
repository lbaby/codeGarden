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
class BinomialQueue : public MergeablePriorityQueue
{
    LinkedList<BinomialTree*> list;

    BinomialTree& FindMinTree () const;
    void AddTree (BinomialTree&);
    void RemoveTree (BinomialTree&);

    static BinomialTree* Sum (
	BinomialTree*, BinomialTree*, BinomialTree*);
    static BinomialTree* Carry (
	BinomialTree*, BinomialTree*, BinomialTree*);
public:
    BinomialQueue ();
    ~BinomialQueue ();
    // ...
};
