//
//   This file contains the C++ code from Program 6.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_14.cpp
//

#ifndef _QUEUEASARRAY_H_
#define _QUEUEASARRAY_H_

#include <Object.h>
#include <Queue.h>
#include <Array.h>
#include <Visitor.h>


class QueueAsArray : public virtual Queue
{
protected:
    Array<Object*> array;
    unsigned int head;
    unsigned int tail;
    int CompareTo(const Object &arg) const;
   
public:
    QueueAsArray (unsigned int);
    ~QueueAsArray ();
     Object& Head () const;
     Object& Dequeue ();
     void Enqueue (Object& object);
      void Accept (Visitor&) const ;
     void Purge(void);
   
    // ...
};

#endif


