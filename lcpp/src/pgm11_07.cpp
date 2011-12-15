//
//   This file contains the C++ code from Program 11.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_07.cpp
//
class LeftistHeap :
    public BinaryTree, public MergeablePriorityQueue
{
    unsigned int nullPathLength;

    void SwapContents (LeftistHeap&);
public:
    LeftistHeap ();
    LeftistHeap (Object&);

    LeftistHeap& Left () const;
    LeftistHeap& Right () const;
    void Merge (MergeablePriorityQueue&);
    // ...
};
