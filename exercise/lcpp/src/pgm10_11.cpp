//
//   This file contains the C++ code from Program 10.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_11.cpp
//
void AVLTree::Balance ()
{
    AdjustHeight ();
    if (abs (BalanceFactor ()) > 1)
    {
	if (BalanceFactor () > 0)
	{
	    if (Left ().BalanceFactor () > 0)
		LLRotation ();
	    else
		LRRotation ();
	}
	else
	{
	    if (Right ().BalanceFactor () < 0)
		RRRotation ();
	    else
		RLRotation ();
	}
    }
}
