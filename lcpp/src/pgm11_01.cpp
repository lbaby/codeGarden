//
//   This file contains the C++ code from Program 11.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_01.cpp
//
class PriorityQueue : public virtual Container
{
public:
    virtual void Enqueue (Object&) = 0;
    virtual Object& FindMin () const = 0;
    virtual Object& DequeueMin () = 0;
};

class MergeablePriorityQueue : public virtual PriorityQueue
{
public:
    virtual void Merge (MergeablePriorityQueue&) = 0;
};

class DoubleEndedPriorityQueue : public virtual PriorityQueue
{
public:
    virtual Object& FindMax () const = 0;
    virtual Object& DequeueMax () = 0;
};
