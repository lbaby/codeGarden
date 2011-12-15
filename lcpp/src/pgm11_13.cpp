//
//   This file contains the C++ code from Program 11.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_13.cpp
//
void BinomialTree::Add (BinomialTree& tree)
{
    if (degree != tree.degree)
	throw invalid_argument ("incompatible degrees");
    if (*key > *tree.key)
	SwapContents (tree);
    AttachSubtree (tree);
}
