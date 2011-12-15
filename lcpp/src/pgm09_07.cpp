//
//   This file contains the C++ code from Program 9.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_07.cpp
//
Tree::Iter::Iter (Tree const& _tree) :
    tree (_tree),
    stack (*new StackAsLinkedList ())
{
    stack.RescindOwnership ();
    Reset ();
}

Tree::Iter::~Iter ()
    { delete &stack; }

void Tree::Iter::Reset ()
{
    stack.Purge ();
    if (!tree.IsEmpty ())
	stack.Push (const_cast<Tree&> (tree));
}
