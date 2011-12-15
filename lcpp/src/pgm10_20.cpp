//
//   This file contains the C++ code from Program 10.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_20.cpp
//
void BTree::Insert (Object& object)
{
    if (IsEmpty ())
    {
	if (parent == 0)
	{
	    AttachSubtree (0, *new BTree (m, *this));
	    AttachKey (1, object);
	    AttachSubtree (1, *new BTree (m, *this));
	    numberOfKeys = 1;
	}
	else
	    parent->InsertPair (object, *new BTree (m, *parent));
    }
    else
    {
	unsigned int const index = FindIndex (object);
	if (index != 0 && object == *key [index])
	    throw invalid_argument ("duplicate key");
	subtree [index]->Insert (object);
    }
}
