//
//   This file contains the C++ code from Program 13.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_02.cpp
//
struct Tag
{
    StoragePool* pool;
};

void* operator new (size_t bytes, StoragePool& p)
{
    Tag* const tag = reinterpret_cast<Tag*> (
	p.Acquire (bytes + sizeof (Tag)));
    tag->pool = &p;
    return tag + 1;
}

void* operator new (size_t bytes)
{
    Tag* const tag = reinterpret_cast<Tag*> (
	std::malloc (bytes + sizeof (Tag));
    tag->pool = 0;
    return tag + 1;
}

void operator delete (void* arg)
{
    Tag* const tag = reinterpret_cast<Tag*> (arg) - 1U;
    if (tag->pool)
	tag->pool->Release (tag);
    else
	std::free (tag);
}
