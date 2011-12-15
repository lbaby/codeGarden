//
//   This file contains the C++ code from Program 10.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_21.cpp
//
void BTree::InsertPair (Object& object, BTree& child)
{
    unsigned int const index = FindIndex (object);
    BTree& extraTree = InsertSubtree (index + 1, child);
    Object& extraKey = InsertKey (index + 1, object);

    if (++numberOfKeys == m)
    {
	if (parent == 0)
	{
	    BTree& left = *new BTree (m, *this);
	    BTree& right = *new BTree (m, *this);
	    left.AttachLeftHalfOf (*this);
	    right.AttachRightHalfOf (*this, extraKey, extraTree);
	    AttachSubtree (0, left);
	    AttachKey (1, *key [(m + 1)/2]);
	    AttachSubtree (1, right);
	    numberOfKeys = 1;
	}
	else
	{
	    numberOfKeys = (m + 1)/2 - 1;
	    BTree& right = *new BTree (m, *parent);
	    right.AttachRightHalfOf (*this, extraKey, extraTree);
	    parent->InsertPair (*key [(m + 1)/2], right);
	}
    }
}
