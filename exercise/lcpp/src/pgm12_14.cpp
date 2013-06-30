//
//   This file contains the C++ code from Program 12.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_14.cpp
//
MultisetAsLinkedList operator + (
    MultisetAsLinkedList const& s, MultisetAsLinkedList const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    MultisetAsLinkedList result (s.universeSize);
    ListElement<unsigned int> const* p = s.list.Head();
    ListElement<unsigned int> const* q = t.list.Head();
    while (p && q)
    {
	if (p->Datum () <= q->Datum ())
	{
	    result.list.Append (p->Datum ());
	    p = p->Next ();
	}
	else
	{
	    result.list.Append (q->Datum ());
	    q = q->Next ();
	}
    }
    for ( ; p; p = p->Next ())
	result.list.Append (p->Datum ());
    for ( ; q; q = q->Next ())
	result.list.Append (q->Datum ());
    return result;
}
