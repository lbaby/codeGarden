//
//   This file contains the C++ code from Program 12.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_22.cpp
//
void PartitionAsForest::Join (Set& s, Set& t)
{
    PartitionTree& p = dynamic_cast<PartitionTree&> (s);
    PartitionTree& q = dynamic_cast<PartitionTree&> (t);
    CheckArguments (p, q);
    if (p.count > q.count)
    {
	q.parent = &p;
	p.count += q.count;
    }
    else
    {
	p.parent = &q;
	q.count += p.count;
    }
    --count;
}
