//
//   This file contains the C++ code from Program 13.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_12.cpp
//
BuddyPool::BuddyPool (size_t bytes) :
    m (Log2Ceil (bytes)),
    numberOfBlocks ((1 << m) / sizeof (Block)),
    pool (new Block [numberOfBlocks + m + 1]),
    sentinel (pool + numberOfBlocks)
{
    for (unsigned int i = 0; i <= m; ++i)
    {
	sentinel [i].link.next = &sentinel [i];
	sentinel [i].link.prev = &sentinel [i];
    }

    Block& head = pool [0];
    head.status = free;
    head.k = m;
    InsertAfter (sentinel [m], head);
}

BuddyPool::~BuddyPool ()
    { delete [] pool; }
