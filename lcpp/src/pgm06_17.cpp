//
//   This file contains the C++ code from Program 6.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_17.cpp
//
class QueueAsLinkedList : public virtual Queue
{
protected:
    LinkedList<Object*> list;
public:
    QueueAsLinkedList ();
    ~QueueAsLinkedList ();
    // ...
};
