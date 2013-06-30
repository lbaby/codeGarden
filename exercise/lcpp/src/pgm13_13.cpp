//
//   This file contains the C++ code from Program 13.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_13.cpp
//
void* BuddyPool::Acquire (size_t bytes)
{
    unsigned int kPrime = Log2Ceil (bytes + sizeof (Header));

    unsigned int i = kPrime;
    while (i <= m && sentinel [i].link.next == &sentinel [i])
	++i;
    if (i > m)
	throw bad_alloc ("out of memory");

    Block& block = *sentinel [i].link.next;
    Unlink (block);
    while (block.k > kPrime)
    {
	block.k -= 1;
	Block& buddy = Buddy (block);
	buddy.status = free;
	buddy.k = block.k;
	InsertAfter (sentinel [buddy.k], buddy);
    }
    block.status = reserved;
    return block.userPart;
}
