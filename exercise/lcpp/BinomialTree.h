#ifndef BINOMIALTREE_H_
#define BINOMIALTREE_H_
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

#include <GeneralTree.h>

class BinomialTree : public GeneralTree
{
    void SwapContents (BinomialTree&);
public:
    BinomialTree (Object& o) :GeneralTree(o)
    {}

    void Add (BinomialTree& );
    
    BinomialTree& Subtree (unsigned int i) const
    {
    	return dynamic_cast< BinomialTree& > (  GeneralTree::Subtree ( i) ) ;
    }
    
};

#endif /*BINOMIALTREE_H_*/
