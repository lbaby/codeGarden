//
//   This file contains the C++ code from Program 10.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_17.cpp
//
void MWayTree::Insert (Object& object)
{
    if (IsEmpty ())
    {
	subtree [0] = new MWayTree (m);
	key [1] = &object;
	subtree [1] = new MWayTree (m);
	numberOfKeys = 1;
    }
    else
    {
	unsigned int const index = FindIndex (object);
	if (index != 0 && object == *key [index])
	    throw invalid_argument ("duplicate key");
	if (numberOfKeys < m - 1U)
	{
	    for(unsigned int i = numberOfKeys; i > index; --i)
	    {
		key [i + 1] = key [i];
		subtree [i + 1] = subtree [i];
	    }
	    key [index + 1] = &object;
	    subtree [index + 1] = new MWayTree (m);
	    ++numberOfKeys;
	}
	else
	    subtree [index]->Insert (object);
    }
}
