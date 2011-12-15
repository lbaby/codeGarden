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

#ifndef CHAINEDSCATTERTABLE_H_
#define CHAINEDSCATTERTABLE_H_

#include <HashTable.h>
#include <Object.h>
#include <Array.h>



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
protected:
   int CompareTo(Object const & arg) const 
   {
   	ChainedScatterTable const &cst = 
   	dynamic_cast<ChainedScatterTable const &>(arg);
   	
   	return (int)(count - cst.count);
   }
      
public:
    ChainedScatterTable (unsigned int);
    void Purge ();
    ~ChainedScatterTable ();
    void Insert (Object& object);
    Object& Find (Object const& object) const;
    void Withdraw (Object& object);
    void Accept(Visitor&) const;
    bool IsFull(void) const
    {
    	return count == length;
    }
    bool IsEmpty(void) const
    {
    	return count  != length;
    }
    
     bool IsMember(const Object&) const;
    // ...
};
#endif /*CHAINEDSCATTERTABLE_H_*/
