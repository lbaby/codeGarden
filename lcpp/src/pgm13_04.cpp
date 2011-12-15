//
//   This file contains the C++ code from Program 13.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_04.cpp
//
SinglyLinkedPool::SinglyLinkedPool (size_t n) :
    numberOfBlocks ((n + sizeof (Block) - 1U) / sizeof (Block)),
    pool (new Block [numberOfBlocks + 1]),
    sentinel (pool [numberOfBlocks])
{
    Block& head = pool [0];
    head.length = numberOfBlocks;
    head.next = 0;

    sentinel.length = 0;
    sentinel.next = &head;
}

SinglyLinkedPool::~SinglyLinkedPool ()
    { delete [] pool; }
