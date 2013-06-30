
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

#ifndef OPENSCATTERTABLE_H_
#define OPENSCATTERTABLE_H_

#include <HashTable.h>
#include <Array.h>
#include <Object.h>
#include <Visitor.h>



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

    unsigned int C (unsigned int i, Object const &object) const;
    unsigned int FindMatch (Object const&) const;
    unsigned int FindInstance (Object const&) const;
    unsigned int FindUnoccupied (Object const&) const;
    
protected:
    int CompareTo(Object const & arg) const;
public:
    OpenScatterTable (unsigned int);
    
        bool IsFull(void) const
    {
    	return count == length;
    }
    bool IsEmpty(void) const
    {
    	return count  != length;
    }
    
    void Purge ();

    void Insert (Object& object);
    Object& Find (Object const& object) const;
    void Withdraw (Object& object);
    
    void Accept(Visitor&) const;
   bool IsMember(const Object&) const;
    // ...
};

#endif /*OPENSCATTERTABLE_H_*/
