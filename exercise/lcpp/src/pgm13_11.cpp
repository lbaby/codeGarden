//
//   This file contains the C++ code from Program 13.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_11.cpp
//
class BuddyPool : public StoragePool
{
public:
    enum Status { free, reserved };
    struct Header
    {
	Status status: 1;
	unsigned int k : bitsizeof (unsigned int) - 1U;
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
    unsigned int m;
    unsigned int numberOfBlocks;
    Block* pool;
    Block* sentinel;

    static void Unlink (Block&);
    static void InsertAfter (Block&, Block&);
    Block& Buddy (Block&) const;
public:
    BuddyPool (size_t);
    ~BuddyPool ();

    void* Acquire (size_t);
    void Release (void*);
};
