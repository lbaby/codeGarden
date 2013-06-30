//
//   This file contains the C++ code from Program 13.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_08.cpp
//
DoublyLinkedPool::DoublyLinkedPool (size_t n) :
    numberOfBlocks ((n + sizeof (Block) - 1U) / sizeof (Block)),
    pool (new Block [numberOfBlocks + 1]),
    sentinel (pool [numberOfBlocks])
{
    sentinel.status = reserved;
    sentinel.link.next = &sentinel;
    sentinel.link.prev = &sentinel;

    Block& head = pool [0];
    head.status = free;
    head.length = numberOfBlocks;
    InsertAfter (sentinel, head);
}

DoublyLinkedPool::~DoublyLinkedPool ()
    { delete [] pool; }
