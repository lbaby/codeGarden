//
//   This file contains the C++ code from Program 11.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_18.cpp
//
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
