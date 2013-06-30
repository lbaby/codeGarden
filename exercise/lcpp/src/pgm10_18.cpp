//
//   This file contains the C++ code from Program 10.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_18.cpp
//
void MWayTree::Withdraw (Object& object)
{
    if (IsEmpty ())
	throw invalid_argument ("object not found");
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
    {
	if (!subtree [index - 1U]->IsEmpty ())
	{
	    Object& max = subtree [index - 1U]->FindMax ();
	    key [index] = &max;
	    subtree [index - 1U]->Withdraw (max);
	}
	else if (!subtree [index]->IsEmpty ())
	{
	    Object& min = subtree [index]->FindMin ();
	    key [index] = &min;
	    subtree [index]->Withdraw (min);
	}
	else
	{
	    --numberOfKeys;
	    delete subtree [index];
	    for(unsigned int i = index; i <= numberOfKeys; ++i)
	    {
		key [i] = key [i + 1];
		subtree [i] = subtree [i + 1];
	    }
	    if (numberOfKeys == 0)
		delete subtree [0];
	}
    }
    else
	subtree [index]->Withdraw (object);
}
