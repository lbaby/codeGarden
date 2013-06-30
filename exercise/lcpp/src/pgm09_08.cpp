//
//   This file contains the C++ code from Program 9.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_08.cpp
//
bool Tree::Iter::IsDone () const
    { return stack.IsEmpty (); }

Object& Tree::Iter::operator * () const
{
    if (!stack.IsEmpty ())
    {
	Tree const& top =
	    dynamic_cast<Tree const&> (stack.Top ());
	return top.Key ();
    }
    else
	return NullObject::Instance ();
}

void Tree::Iter::operator ++ ()
{
    if (!stack.IsEmpty ())
    {
	Tree const& top =
	    dynamic_cast<Tree const&> (stack.Pop ());

	for (int i = top.Degree () - 1; i >= 0; --i)
	{
	    Tree& subtree = top.Subtree (i);
	    if (!subtree.IsEmpty ())
		stack.Push (subtree);
	}
    }
}
