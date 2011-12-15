//
//   This file contains the C++ code from Program 8.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_17.cpp
//
class OpenScatterTable : public HashTable
{
    class Entry
    {
    public:
	enum State { empty, occupied, deleted };
	State state;
	Object* object;

	Entry ();
    };

    Array<Entry> array;

    unsigned int C (unsigned int) const;
    unsigned int FindMatch (Object const&) const;
    unsigned int FindInstance (Object const&) const;
    unsigned int FindUnoccupied (Object const&) const;
public:
    OpenScatterTable (unsigned int);
    // ...
};
