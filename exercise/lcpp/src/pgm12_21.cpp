//
//   This file contains the C++ code from Program 12.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_21.cpp
//
Set& PartitionAsForest::Find (Object const& object) const
{
    unsigned int const item =
	dynamic_cast<Set::Element const&> (object);
    PartitionTree* root = array [item];
    while (root->parent != 0)
	root = root->parent;
    PartitionTree* ptr = array [item];
    while (ptr->parent != 0)
    {
	PartitionTree* const tmp = ptr->parent;
	ptr->parent = root;
	ptr = tmp;
    }
    return *root;
}
