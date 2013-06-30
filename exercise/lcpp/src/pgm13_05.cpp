//
//   This file contains the C++ code from Program 13.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_05.cpp
//
void* SinglyLinkedPool::Acquire (size_t bytes)
{
    unsigned int const blocks =
	(bytes + sizeof (Header) + sizeof (Block) - 1U) /
	    sizeof (Block);

    Block* prevPtr = &sentinel;
    Block* ptr = prevPtr->next;
    while (ptr != 0 && ptr->length < blocks)
    {
	prevPtr = ptr;
	ptr = ptr->next;
    }
    if (ptr == 0)
	throw bad_alloc ("out of memory");
    if (ptr->length > blocks)
    {
	Block& newBlock = ptr [blocks];
	newBlock.length = ptr->length - blocks;
	newBlock.next = ptr->next;
	ptr->length = blocks;
	ptr->next = &newBlock;
    }
    prevPtr->next = ptr->next;
    return ptr->userPart;
}
