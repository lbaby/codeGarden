#include <BinomialQueue.h>

#include <stdexcept>

//
//   This file contains the C++ code from Program 11.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_15.cpp
//
void BinomialQueue::AddTree (BinomialTree& tree)
{
    list.Append (&tree);
    count += tree.Count ();
}

void BinomialQueue::RemoveTree (BinomialTree& tree)
{
    list.Extract (&tree);
    count -= tree.Count ();
}



BinomialTree& BinomialQueue::FindMinTree (void) const
{
    ListElement<BinomialTree*> const* ptr;

    BinomialTree* minTree = 0;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
    {
	BinomialTree* tree = ptr->Datum ();
	if (minTree == 0 || tree->Key () < minTree->Key ())
	    minTree = tree;
    }
    return *minTree;
}

Object& BinomialQueue::FindMin () const
{
    if (count == 0)
	throw std::domain_error ("priority queue is empty");
    return FindMinTree ().Key ();
}



void BinomialQueue::Merge (MergeablePriorityQueue& queue)
{
    BinomialQueue& arg = dynamic_cast<BinomialQueue&> (queue);
    LinkedList<BinomialTree*> oldList = list;
    list.Purge ();
    count = 0;
    ListElement<BinomialTree*> const* p =
	oldList.Head ();
    ListElement<BinomialTree*> const* q =
	arg.list.Head();
    BinomialTree* carry = 0;
    for (unsigned int i = 0; p || q || carry; ++i)
    {
	BinomialTree* a = 0;
	if (p && p->Datum ()->Degree () == i)
	    { a = p->Datum (); p = p->Next (); }
	BinomialTree* b = 0;
	if (q && q->Datum ()->Degree () == i)
	    { b = q->Datum (); q = q->Next (); }
	BinomialTree* sum = Sum (a, b, carry);
	if (sum)
	    AddTree (*sum);
	carry = Carry (a, b, carry);
    }
    arg.list.Purge ();
    arg.count = 0;
}


BinomialTree* BinomialQueue::Sum (
    BinomialTree* a, BinomialTree* b, BinomialTree* c)
{
    if (a && !b && !c)
	return a;
    else if (!a && b && !c)
	return b;
    else if (!a && !b && c)
	return c;
    else if (a && b && c)
	return c;
    else
	return 0;
}

BinomialTree* BinomialQueue::Carry (
    BinomialTree* a, BinomialTree* b, BinomialTree* c)
{
    if (a && b && !c)
	{ a->Add (*b); return a; }
    else if (a && !b && c)
	{ a->Add (*c); return a; }
    else if (!a && b && c)
	{ b->Add (*c); return b; }
    else if (a && b && c)
	{ a->Add (*b); return a; }
    else
	return 0;
}


void BinomialQueue::Enqueue (Object& object)
{
    BinomialQueue queue;
    queue.AddTree (*new BinomialTree (object));
    Merge (queue);
}


Object& BinomialQueue::DequeueMin ()
{
    if (count == 0)
	throw std::domain_error ("priority queue is empty");

    BinomialTree& minTree = FindMinTree ();
    RemoveTree (minTree);

    BinomialQueue queue;
    while (minTree.Degree () > 0)
    {
	BinomialTree& child = minTree.Subtree (0);

	minTree.DetachSubtree (child);
	queue.AddTree (child);
    }
    Merge (queue);

    Object& result = minTree.Key ();
    minTree.RescindOwnership ();
    delete &minTree;

    return result;
}

void BinomialQueue::Purge(void)
{
	if(IsOwner()){
		list.Purge();
	}
	
}

void BinomialQueue::Accept(Visitor& visitor) const
{
	    ListElement<BinomialTree*> const* ptr;
	for(ptr = list.Head(); ptr; ptr = ptr->Next()){
		BinomialTree* tree = ptr->Datum();
		tree->Accept(visitor);
	}
	
}

 int BinomialQueue::CompareTo(const Object&) const
 {
 	
 	return 0;
 }




