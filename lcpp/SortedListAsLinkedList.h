
//
//   This file contains the C++ code from Program 7.26 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_26.cpp
//

#ifndef SORTEDLISTASLINKEDLIST_H_
#define SORTEDLISTASLINKEDLIST_H_

#include <SortedList.h>
#include <ListAsLinkedList.h>
#include <Object.h>


class SortedListAsLinkedList :
    public virtual SortedList, public virtual ListAsLinkedList
{
public:
    SortedListAsLinkedList () :ListAsLinkedList()
    {}
    void Insert(Object &o);
    // ...
};

#endif /*SORTEDLISTASLINKEDLIST_H_*/
