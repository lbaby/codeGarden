//
//   This file contains the C++ code from Program 11.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_15.cpp
//
void BinomialQueue::AddTree (BinomialTree& tree)
{
    list.Append (&tree);
    count += tree.Count ();
}

void BinomialQueue::RemoveTree (BinomialTree& tree)
{
    list.Extract (&tree);
    count -= tree.Count ();
}
