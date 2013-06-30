//
//   This file contains the C++ code from Program 6.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_07.cpp
//
class StackAsLinkedList : public Stack
{
    LinkedList<Object*> list;

    class Iter;
public:
    StackAsLinkedList ();
    // ...
    friend class Iter;
};

class StackAsLinkedList::Iter : public Iterator
{
    StackAsLinkedList const& stack;
    ListElement<Object*> const* position;
public:
    Iter (StackAsLinkedList const&);
    // ...
};
