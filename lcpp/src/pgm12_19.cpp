//
//   This file contains the C++ code from Program 12.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_19.cpp
//
Set& PartitionAsForest::Find (Object const& object) const
{
    unsigned int const item =
	dynamic_cast<Set::Element const&> (object);
    PartitionTree* ptr = array [item];
    while (ptr->parent != 0)
	ptr = ptr->parent;
    return *ptr;
}
