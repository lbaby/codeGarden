//
//   This file contains the C++ code from Program 8.22 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_22.cpp
//
void OpenScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("scatter table is empty");
    unsigned int i = FindInstance (object);
    if (i == length)
	throw invalid_argument ("object not found");
    for (;;)
    {
	unsigned int j;
	for (j = (i + 1) % length;
	    array [j].state == Entry::occupied;
	    j = (j + 1) % length)
	{
	    unsigned int const h = H (*array [j].object);
	    if ((h <= i && i < j) || (i < j && j < h) ||
		(j < h && h <= i))
		break;
	}
	if (array [j].state == Entry::empty)
	    break;
	array [i] = array [j];
	i = j;
    }
    array [i].state = Entry::empty;
    array [i].object = 0;
    --count;
}
