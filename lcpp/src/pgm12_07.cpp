//
//   This file contains the C++ code from Program 12.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_07.cpp
//
SetAsBitVector::SetAsBitVector (unsigned int n) :
    Set (n),
    vector ((n + wordBits - 1U) / wordBits)
{
    for (unsigned int i = 0; i < vector.Length (); ++i)
	vector [i] = 0;
}

void SetAsBitVector::Insert (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    vector [item / wordBits] |= 1 << item % wordBits;
}

void SetAsBitVector::Withdraw (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    vector [item / wordBits] &= ~(1 << item % wordBits);
}

bool SetAsBitVector::IsMember (Object const& object) const
{
    unsigned int const item =
	dynamic_cast<Element const&> (object);
    return vector [item / wordBits] & (1 << item % wordBits);
}
