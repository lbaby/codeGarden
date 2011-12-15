//
//   This file contains the C++ code from Program 13.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_09.cpp
//
void DoublyLinkedPool::Release (void* arg)
{
    Block& block = *reinterpret_cast<Block*> (
	reinterpret_cast<Header*> (arg) - 1U);

    if (&block < pool || &block >= pool + numberOfBlocks)
	throw invalid_argument ("invalid block");
    
    block.status = free;
    InsertAfter (sentinel, block);
}
