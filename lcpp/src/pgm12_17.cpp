//
//   This file contains the C++ code from Program 12.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_17.cpp
//
class PartitionTree : public Set, public Tree
{
    unsigned int const item;
    PartitionTree* parent;
    unsigned int rank;

    PartitionTree (unsigned int, unsigned int);
    // ...
    friend class PartitionAsForest;
};

class PartitionAsForest : public Partition
{
    Array<PartitionTree*> array;

    void CheckArguments (
	PartitionTree const&, PartitionTree const&);
public:
    PartitionAsForest (unsigned int);
    ~PartitionAsForest ();
    // ...
};

