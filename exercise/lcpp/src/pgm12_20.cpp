//
//   This file contains the C++ code from Program 12.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_20.cpp
//
void PartitionAsForest::CheckArguments (
    PartitionTree const& s, PartitionTree const& t)
{
    if (!IsMember (s) || s.parent != 0 ||
	!IsMember (t) || t.parent != 0 || s == t)
	throw invalid_argument ("incompatible sets");
}

void PartitionAsForest::Join (Set& s, Set& t)
{
    PartitionTree& p = dynamic_cast<PartitionTree&> (s);
    PartitionTree& q = dynamic_cast<PartitionTree&> (t);
    CheckArguments (p, q);
    q.parent = &p;
    --count;
}
