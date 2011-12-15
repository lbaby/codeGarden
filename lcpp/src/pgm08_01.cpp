//
//   This file contains the C++ code from Program 8.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_01.cpp
//
typedef unsigned int HashValue;

HashValue Hash (char c)
    { return abs (c); }

HashValue Hash (int i)
    { return abs (i); }
