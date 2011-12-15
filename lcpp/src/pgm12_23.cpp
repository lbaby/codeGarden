//
//   This file contains the C++ code from Program 12.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_23.cpp
//
void PartitionAsForest::Join (Set& s, Set& t)
{
    PartitionTree& p = dynamic_cast<PartitionTree&> (s);
    PartitionTree& q = dynamic_cast<PartitionTree&> (t);
    CheckArguments (p, q);
    if (p.rank > q.rank)
	q.parent = &p;
    else
    {
	p.parent = &q;
	if (p.rank == q.rank)
	    q.rank += 1;
    }
    --count;
}
