//
//   This file contains the C++ code from Program 13.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_10.cpp
//
void* DoublyLinkedPool::Acquire (size_t bytes)
{
    unsigned int const blocks =
	(bytes + sizeof (Header) + sizeof (Block) - 1U) /
	    sizeof (Block);

    Block* ptr;
    for (ptr = sentinel.link.next; ptr != &sentinel;
	ptr = ptr->link.next)
    {
	for (;;)
	{
	    Block& successor = ptr [ptr->length];
	    if (successor.status == reserved)
		break;
	    Unlink (successor);
	    ptr->length += successor.length;
	}
	if (ptr->length >= blocks)
	    break;
    }
    if (ptr == &sentinel)
	throw bad_alloc ("out of memory");
    if (ptr->length > blocks)
    {
	Block& newBlock = ptr [blocks];
	newBlock.status = free;
	newBlock.length = ptr->length - blocks;
	ptr->length = blocks;
	InsertAfter (sentinel, newBlock);
    }
    Unlink (*ptr);
    ptr->status = reserved;
    return ptr->userPart;
}
