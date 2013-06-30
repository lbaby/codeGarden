//
//   This file contains the C++ code from Program 12.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_13.cpp
//
class MultisetAsLinkedList : public Multiset
{
    LinkedList<unsigned int> list;
public:
    MultisetAsLinkedList (unsigned int);
    // ...
};
