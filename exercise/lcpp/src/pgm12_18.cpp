//
//   This file contains the C++ code from Program 12.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_18.cpp
//
PartitionTree::PartitionTree (unsigned int i, unsigned int n) :
    Set (n),
    item (i),
    parent (0),
    rank (0)
    { count = 1; }

PartitionAsForest::PartitionAsForest (unsigned int n) :
    Partition (n),
    array (n)
{
    for (unsigned int item = 0; item < universeSize; ++item)
	array [item] = new PartitionTree (item, universeSize);
    count = n;
}

PartitionAsForest::~PartitionAsForest ()
{
    for (unsigned int item = 0; item < universeSize; ++item)
	delete array [item];
}
