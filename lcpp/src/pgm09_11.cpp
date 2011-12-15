//
//   This file contains the C++ code from Program 9.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_11.cpp
//
Object& GeneralTree::Key () const
    { return *key; }

GeneralTree& GeneralTree::Subtree (unsigned int i) const
{
    if (i >= degree)
	throw out_of_range ("invalid subtree index");

    unsigned int j = 0;
    ListElement<GeneralTree*> const* ptr =
	list.Head ();
    while (j < i && ptr != 0)
    {
	++j;
	ptr = ptr->Next ();
    }
    if (ptr == 0)
	throw logic_error ("should never happen");
    return *ptr->Datum ();
}

void GeneralTree::AttachSubtree (GeneralTree& t)
{
    list.Append (&t);
    ++degree;
}

GeneralTree& GeneralTree::DetachSubtree (GeneralTree& t)
{
    list.Extract (&t);
    --degree;
    return t;
}
