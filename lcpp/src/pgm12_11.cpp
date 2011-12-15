//
//   This file contains the C++ code from Program 12.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_11.cpp
//
MultisetAsArray::MultisetAsArray (unsigned int n) :
    Multiset (n),
    array (n)
{
    for (unsigned int item = 0; item < universeSize; ++item)
	array [item] = 0;
}

void MultisetAsArray::Insert (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    ++array [item];
}

void MultisetAsArray::Withdraw (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    if (array [item] > 0)
	--array [item];
}

bool MultisetAsArray::IsMember (Object const& object) const
{
    unsigned int const item =
	dynamic_cast<Element const&> (object);
    return array [item] > 0;
}
