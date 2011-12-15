//
//   This file contains the C++ code from Program 13.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_14.cpp
//
void BuddyPool::Release (void* arg)
{
    Block& block = *reinterpret_cast<Block*> (
	reinterpret_cast<Header*> (arg) - 1U);

    if (&block < pool || &block >= pool + numberOfBlocks)
	throw invalid_argument ("invalid pointer");

    block.status = free;
    Block* ptr;
    for (ptr = &block; ptr->k < m; ptr->k += 1)
    {
	Block& buddy = Buddy (*ptr);
	if (buddy.status == reserved || buddy.k != ptr->k)
	    break;
	Unlink (buddy);
	if (&buddy < ptr)
	    ptr = &buddy;
    }
    InsertAfter (sentinel [ptr->k], *ptr);
}
