//
//   This file contains the C++ code from Program 10.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_07.cpp
//
class AVLTree : public BST
{
protected:
    int height;

    int BalanceFactor () const;
    void AdjustHeight ();
    void LLRotation ();
    void LRRotation ();
    void RRRotation ();
    void RLRotation ();
    void AttachKey (Object&);
    Object& DetachKey ();
    void Balance ();
public:
    AVLTree ();

    int Height () const;
    AVLTree& Left () const;
    AVLTree& Right () const;
};
