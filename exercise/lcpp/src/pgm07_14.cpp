//
//   This file contains the C++ code from Program 7.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_14.cpp
//
class ListAsLinkedList::Pos : public Position
{
    ListAsLinkedList const& list;
    ListElement<Object*> const* element;
public:
    // ...
    friend class ListAsLinkedList;
};
