//
//   This file contains the C++ code from Program 9.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_10.cpp
//
GeneralTree::GeneralTree (Object& _key) :
    key (&_key),
    degree (0),
    list ()
    {}

void GeneralTree::Purge ()
{
    ListElement<GeneralTree*> const* ptr;

    if (IsOwner ())
	delete key;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	delete ptr->Datum ();
    key = 0;
    list.Purge ();
}

GeneralTree::~GeneralTree ()
    { Purge (); }
