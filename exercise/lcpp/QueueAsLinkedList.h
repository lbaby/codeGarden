
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

#ifndef QUEUEASLINKEDLIST_H_
#define QUEUEASLINKEDLIST_H_

#include <Object.h>
#include <Queue.h>
#include <LinkedList.h>
#include <Visitor.h>

class QueueAsLinkedList : public virtual Queue
{
protected:
    LinkedList<Object*> list;
    int CompareTo(Object const & arg) const
    {
    	QueueAsLinkedList const &o = 
    	dynamic_cast<QueueAsLinkedList const &> ( arg);
    	return (int)(count - o.count);
    }
public:
    QueueAsLinkedList ();
    ~QueueAsLinkedList ();
         Object& Head () const;
     Object&  Dequeue ();
     void  Enqueue (Object& object);
      void Accept (Visitor&) const ;
     void Purge(void);
    // ...
};
#endif /*QUEUEASLINKEDLIST_H_*/
