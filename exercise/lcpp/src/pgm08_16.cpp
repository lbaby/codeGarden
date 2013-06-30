//
//   This file contains the C++ code from Program 8.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_16.cpp
//
void ChainedScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("scatter table is empty");
    unsigned int i = H (object);
    while (i != Entry::null && array [i].object != &object)
	i = array [i].next;
    if (i == Entry::null)
	throw invalid_argument ("object not found");
    for (;;)
    {
	unsigned int j;
	for (j = array [i].next;
	    j != Entry::null; j = array [j].next)
	{
	    unsigned int const h = H (*array [j].object);
	    bool contained = false;
	    for (unsigned int k = array [i].next;
		k != array [j].next && !contained;
		k = array [k].next)
	    {
		if (k == h)
		    contained = true;
	    }
	    if (!contained)
		break;
	}
	if (j == Entry::null)
	    break;
	array [i].object = array [j].object;
	i = j;
    }
    array [i].object = 0;
    array [i].next = Entry::null;
    for (unsigned int j = (i + length - 1U) % length;
	j != i; j = (j + length - 1U) % length)
    {
	if (array [j].next == i)
	{
	    array [j].next = Entry::null;
	    break;
	}
    }
    --count;
}
