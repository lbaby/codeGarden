//
//   This file contains the C++ code from Program 13.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_06.cpp
//
void SinglyLinkedPool::Release (void* arg)
{
    Block& block = *reinterpret_cast<Block*> (
	reinterpret_cast<Header*> (arg) - 1U);
    
    if (&block < pool || &block >= pool + numberOfBlocks)
	throw invalid_argument ("invalid block");

    Block* prevPtr = &sentinel;
    Block* ptr = prevPtr->next;
    while (ptr != 0 && ptr < &block)
    {
	prevPtr = ptr;
	ptr = ptr->next;
    }
    if (ptr != 0 && &block + block.length == ptr)
    {
	block.length += ptr->length;
	block.next = ptr->next;
    }
    else
	block.next = ptr;
    if (prevPtr + prevPtr->length == &block)
    {
	prevPtr->length += block.length;
	prevPtr->next = block.next;
    }
    else
	prevPtr->next = &block;
}
