//
//   This file contains the C++ code from Program 9.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_05.cpp
//
void Tree::Accept (Visitor& visitor) const
    { DepthFirstTraversal (PreOrder (visitor)); }
