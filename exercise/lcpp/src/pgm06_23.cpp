//
//   This file contains the C++ code from Program 6.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_23.cpp
//
class DequeAsArray : public Deque, public QueueAsArray
{
public:
    DequeAsArray (unsigned int);
    // ...
};
