//
//   This file contains the C++ code from Program 12.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_15.cpp
//
MultisetAsLinkedList operator * (
    MultisetAsLinkedList const& s, MultisetAsLinkedList const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    MultisetAsLinkedList result (s.universeSize);
    ListElement<unsigned int> const* p = s.list.Head();
    ListElement<unsigned int> const* q = t.list.Head();
    while (p && q)
    {
	int const diff = p->Datum () - q->Datum ();
	if (diff == 0)
	    result.list.Append (p->Datum ());
	if (diff <= 0)
	    p = p->Next ();
	if (diff >= 0)
	    q = q->Next ();
    }
    return result;
}
