//
//   This file contains the C++ code from Program 10.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_19.cpp
//
class BTree : public MWayTree
{
    BTree* parent;

    void InsertPair (Object&, BTree&);
    void AttachKey (unsigned int, Object&);
    void AttachSubtree (unsigned int, MWayTree&);
    Object& InsertKey (unsigned int, Object&);
    BTree& InsertSubtree (unsigned int, BTree&);
    void AttachLeftHalfOf (BTree const&);
    void AttachRightHalfOf (BTree const&, Object&, BTree&);
public:
    BTree (unsigned int);
    BTree (unsigned int, BTree&);

    void Insert (Object&);
    void Withdraw (Object&);
};
