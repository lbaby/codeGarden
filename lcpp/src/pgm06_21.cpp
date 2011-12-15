//
//   This file contains the C++ code from Program 6.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_21.cpp
//
class Deque : public virtual Queue
{
public:
    virtual Object& Head () const = 0;
    virtual Object& Tail () const = 0;
    virtual void Enqueue (Object&);
    virtual void EnqueueHead (Object&) = 0;
    virtual void EnqueueTail (Object&) = 0;
    virtual Object& Dequeue ();
    virtual Object& DequeueHead () = 0;
    virtual Object& DequeueTail () = 0;
};
