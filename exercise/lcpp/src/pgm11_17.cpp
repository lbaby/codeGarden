//
//   This file contains the C++ code from Program 11.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_17.cpp
//
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
