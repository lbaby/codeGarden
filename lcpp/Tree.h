//
//   This file contains the C++ code from Program 9.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_01.cpp
//
#ifndef _TREE_H_
#define _TREE_H_

#include <Container.h>
#include <Visitor.h>
#include <PrePostVisitor.h>
#include <Iterator.h>
#include  <Stack.h>
#include <Object.h>

#include <ostream>




class Tree : public virtual Container
{
    class Iter;
public:
    virtual Object& Key () const = 0;
    virtual Tree& Subtree (unsigned int) const = 0;
    virtual bool IsEmpty () const = 0;
    virtual bool IsLeaf () const = 0;
    virtual unsigned int Degree () const = 0;
    virtual int Height () const
    {
    	return 0;
    }
    virtual void DepthFirstTraversal (PrePostVisitor&) const;
    virtual void BreadthFirstTraversal (Visitor&) const;
    void Accept (Visitor&) const;
     virtual Iterator& NewIterator () const;

    
};


class Tree::Iter : public Iterator
{
	Tree const  &tree;
	Stack &stack;
public:
	Iter(Tree const &);
	~Iter();
	void Reset();
	bool IsDone() const;
	Object &operator * () const;
	void operator ++();
};


#endif /*TREE_H_*/
