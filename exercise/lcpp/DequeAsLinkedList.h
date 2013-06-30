//
//   This file contains the C++ code from Program 6.26 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_26.cpp
//

#ifndef DEQUEASLINKEDLIST_H_
#define DEQUEASLINKEDLIST_H_

#include <Object.h>
#include <Deque.h>
#include <QueueAsLinkedList.h>


class DequeAsLinkedList : public Deque, public QueueAsLinkedList
{
	int CompareTo(const Object&) const 
	{
		return 0;
	}


public:
    DequeAsLinkedList ()
    {}
        Object& Head () const;
    void EnqueueTail (Object& object);
    Object& DequeueHead ();
    Object& Tail () const;
    void EnqueueHead (Object& object);
    Object& DequeueTail ();
    // ...
};

#endif /*DEQUEASLINKEDLIST_H_*/
