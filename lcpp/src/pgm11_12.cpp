//
//   This file contains the C++ code from Program 11.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_12.cpp
//
class BinomialTree : public GeneralTree
{
    void SwapContents (BinomialTree&);
public:
    BinomialTree (Object&);

    void Add (BinomialTree&);
    BinomialTree& Subtree (unsigned int) const;
};
