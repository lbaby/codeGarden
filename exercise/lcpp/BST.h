//
//   This file contains the C++ code from Program 10.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_02.cpp
//


#ifndef BST_H_
#define BST_H_

#include <Object.h>
#include <BinaryTree.h>
#include <SearchTree.h>

class BST : public BinaryTree, public SearchTree
{
protected:
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void Balance ();
public:
    BST& Left () const;
    BST& Right () const;
    bool IsMember(const Object&) const;
    
    Object& Find (Object const& object) const;
    Object& FindMin () const;
    Object& FindMax () const;
    void Insert (Object& object);
    void Withdraw (Object& object);
 
    
};


#endif /*BST_H_*/
