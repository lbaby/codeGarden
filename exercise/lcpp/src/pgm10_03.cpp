//
//   This file contains the C++ code from Program 10.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_03.cpp
//
BST& BST::Left () const
    { return dynamic_cast<BST&> (BinaryTree::Left ()); }

BST& BST::Right () const
    { return dynamic_cast<BST&> (BinaryTree::Right ()); }
