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
class QueueAsArray : public virtual Queue
{
protected:
    Array<Object*> array;
    unsigned int head;
    unsigned int tail;
public:
    QueueAsArray (unsigned int);
    ~QueueAsArray ();
    // ...
};
