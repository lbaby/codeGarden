//
//   This file contains the C++ code from Program 13.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_07.cpp
//
class DoublyLinkedPool : public StoragePool
{
public:
    enum Status { free, reserved };
    struct Header
    {
	Status status : 1;
	unsigned int length : bitsizeof (unsigned int) - 1U;
    };
    struct Block : public Header
    {
	enum { size = 16 };
	struct Links
	{
	    Block* next;
	    Block* prev;
	};
	union
	{
	    Links link;
	    char userPart [size - sizeof (Header)];
	};
    };
private:
    unsigned int numberOfBlocks;
    Block* pool;
    Block& sentinel;

    static void Unlink (Block&);
    static void InsertAfter (Block&, Block&);
public:
    DoublyLinkedPool (size_t);
    ~DoublyLinkedPool ();

    void* Acquire (size_t);
    void Release (void*);
};
