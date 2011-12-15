//
//   This file contains the C++ code from Program 13.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_03.cpp
//
class SinglyLinkedPool : public StoragePool
{
public:
    struct Header
    {
	unsigned int length;
    };
    struct Block : public Header
    {
	enum { size = 16 };
	union
	{
	    Block* next;
	    char userPart [size - sizeof (Header)];
	};
    };
private:
    unsigned int numberOfBlocks;
    Block* pool;
    Block& sentinel;
public:
    SinglyLinkedPool (size_t);
    ~SinglyLinkedPool ();

    void* Acquire (size_t);
    void Release (void*);
};
