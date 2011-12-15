//
//   This file contains the C++ code from Program 12.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_03.cpp
//
#include <SetAsArray.h>
#include <stdexcept>

SetAsArray::SetAsArray (unsigned int n) :
    Set (n),
    array (n)
{
    for (unsigned int item = 0; item < universeSize; ++item)
	array [item] = false;
}

void SetAsArray::Insert (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    array [item] = true;
}

bool SetAsArray::IsMember (Object const& object) const
{
    unsigned int const item =
	dynamic_cast<Element const&> (object);
    return array [item];
}

void SetAsArray::Withdraw (Object& object)
{
    unsigned int const item = dynamic_cast<Element&> (object);
    array [item] = false;
}


SetAsArray operator + (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw std::invalid_argument ("mismatched sets");
    SetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	result.array [i] = s.array [i] || t.array [i];
    return result;
}

SetAsArray operator * (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw std::invalid_argument ("mismatched sets");
    SetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	result.array [i] = s.array [i] && t.array [i];
    return result;
}

SetAsArray operator - (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw std::invalid_argument ("mismatched sets");
    SetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	result.array [i] = s.array [i] && !t.array [i];
    return result;
}



bool operator == (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw std::invalid_argument ("mismatched sets");
    for (unsigned int item = 0; item < s.universeSize; ++item)
	if (s.array [item] != t.array [item])
	    return false;
    return true;
}

bool operator <= (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw std::invalid_argument ("mismatched sets");
    for (unsigned int item = 0; item < s.universeSize; ++item)
	if (s.array [item] && !t.array [item])
	    return false;
    return true;
}
