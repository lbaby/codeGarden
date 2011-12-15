//
//   This file contains the C++ code from Program 9.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_16.cpp
//
class BinaryTree : public virtual Tree
{
protected:
    Object* key;
    BinaryTree* left;
    BinaryTree* right;
public:
    BinaryTree ();
    BinaryTree (Object&);
    ~BinaryTree ();

    Object& Key () const;
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual BinaryTree& Left () const;
    virtual BinaryTree& Right () const;
    virtual void AttachLeft (BinaryTree&);
    virtual void AttachRight (BinaryTree&);
    virtual BinaryTree& DetachLeft ();
    virtual BinaryTree& DetachRight ();
    // ...
};
