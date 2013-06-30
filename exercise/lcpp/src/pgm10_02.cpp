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
class BST : public BinaryTree, public SearchTree
{
protected:
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void Balance ();
public:
    BST& Left () const;
    BST& Right () const;
    // ...
};
