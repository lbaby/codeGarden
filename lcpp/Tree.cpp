

//
//   This file contains the C++ code from Program 9.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_02.cpp
//

#include "Tree.h"

#include <Queue.h>
#include <QueueAsLinkedList.h>
#include <StackAsLinkedList.h>
#include <NullObject.h>






void Tree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (visitor.IsDone ())
	return;
    if (!IsEmpty ())
    {
	visitor.PreVisit (Key ());
	for (unsigned int i = 0; i < Degree (); ++i)
	    Subtree (i).DepthFirstTraversal (visitor);
	visitor.PostVisit (Key ());
    }
}


void Tree::BreadthFirstTraversal (Visitor& visitor) const
{
    Queue& queue = *new QueueAsLinkedList ();
    queue.RescindOwnership ();

    if (!IsEmpty ())
	queue.Enqueue (const_cast<Tree&> (*this));
    while (!queue.IsEmpty () && !visitor.IsDone ())
    {
	Tree const& head =
	    dynamic_cast<Tree const &> (queue.Dequeue ());

	visitor.Visit (head.Key ());
	for (unsigned int i = 0; i < head.Degree (); ++i)
	{
	    Tree& child = head.Subtree (i);
	    if (!child.IsEmpty ())
		queue.Enqueue (child);
	}
    }
    delete &queue;
}

void Tree::Accept (Visitor& visitor) const
    {
    	 PreOrder pre (visitor);
    	DepthFirstTraversal (pre );
    	////////////
    	}


      Iterator& Tree::NewIterator () const
     {
     	return *new Iter(*this);
     }
     


    Tree::Iter::Iter (Tree const& _tree) :
    tree (_tree),
    stack (*new StackAsLinkedList ())
{
    stack.RescindOwnership ();
    Reset ();
}

Tree::Iter::~Iter ()
    { delete &stack; }

void Tree::Iter::Reset ()
{
    stack.Purge ();
    if (!tree.IsEmpty ())
	stack.Push (const_cast<Tree&> (tree));
}
    
    
bool Tree::Iter::IsDone () const
    { return stack.IsEmpty (); }

Object& Tree::Iter::operator * () const
{
    if (!stack.IsEmpty ())
    {
	Tree const& top =
	    dynamic_cast<Tree const&> (stack.Top ());
	return top.Key ();
    }
    else
	return NullObject::Instance ();
}

void Tree::Iter::operator ++ ()
{
    if (!stack.IsEmpty ())
    {
	Tree const& top =
	    dynamic_cast<Tree const&> (stack.Pop ());

	for (int i = top.Degree () - 1; i >= 0; --i)
	{
	    Tree& subtree = top.Subtree (i);
	    if (!subtree.IsEmpty ())
		stack.Push (subtree);
	}
    }
}

