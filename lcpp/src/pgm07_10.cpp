//
//   This file contains the C++ code from Program 7.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_10.cpp
//
class ListAsLinkedList : public virtual OrderedList
{
protected:
    LinkedList<Object*> linkedList;

    class Pos;
public:
    ListAsLinkedList ();
    // ...
    friend class Pos;
};
