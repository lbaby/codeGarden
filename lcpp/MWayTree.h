//
//   This file contains the C++ code from Program 10.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_13.cpp
//
#ifndef MWAYTREE_H_
#define MWAYTREE_H_

#include <Object.h>
#include <SearchTree.h>
#include <Array.h>


class MWayTree : public SearchTree
{
protected:
    unsigned int const m;
    unsigned int numberOfKeys;
    Array<Object*> key;
    Array<MWayTree*> subtree;
    
    int CompareTo(const Object& object) const
    {
    	const MWayTree &mwt = dynamic_cast<const MWayTree &> (object);
    	
    	return (int)(m - mwt.m);
    }
    
    

    unsigned int FindIndex (Object const&) const;
public:
    MWayTree (unsigned int);
    ~MWayTree ()
    {
    	Purge();
    }
    
    bool IsEmpty() const
    {
    	return !numberOfKeys ;
    }
    
    unsigned int Count() const ;
    
    Object& Key () const
    {
	return Key(1);
	}
	
	bool IsLeaf() const
	{
		return !IsEmpty() && !Degree();
	}
	
	unsigned int Degree() const;
	
	Object& FindMin() const;
	Object& FindMax() const;
	
    Object& Key (unsigned int i) const
    {
    	return *key[i ];
    }
    
     bool IsMember(const Object& arg) const
     {
     	const Object &o = Find(arg);
     	return &o == &arg;
     }
     
    MWayTree& Subtree (unsigned int) const;
    void DepthFirstTraversal (PrePostVisitor& visitor) const;
    void Insert(Object&);
    Object& Find (Object const& object) const;
    void Withdraw (Object& object);
    void Purge(void);
};

#endif /*MWAYTREE_H_*/
