//
//   This file contains the C++ code from Program 8.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_13.cpp
//
class ChainedScatterTable : public HashTable
{
    class Entry
    {
    public:
	enum { null = ~0U };
	Object* object;
	unsigned int next;

	Entry ();
    };

    Array<Entry> array;
public:
    ChainedScatterTable (unsigned int);
    // ...
};
