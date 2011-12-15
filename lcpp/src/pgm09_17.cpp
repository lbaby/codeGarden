//
//   This file contains the C++ code from Program 9.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_17.cpp
//
BinaryTree::BinaryTree () :
    key (0),
    left (0),
    right (0)
    {}

BinaryTree::BinaryTree (Object& _key) :
    key (&_key),
    left (new BinaryTree ()),
    right (new BinaryTree ())
    {}
