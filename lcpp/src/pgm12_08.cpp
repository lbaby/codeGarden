//
//   This file contains the C++ code from Program 12.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_08.cpp
//
SetAsBitVector operator + (
    SetAsBitVector const& s, SetAsBitVector const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    SetAsBitVector result (s.universeSize);
    for (unsigned int i = 0; i < s.vector.Length (); ++i)
	result.vector [i] = s.vector [i] | t.vector [i];
    return result;
}

SetAsBitVector operator * (
    SetAsBitVector const& s, SetAsBitVector const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    SetAsBitVector result (s.universeSize);
    for (unsigned int i = 0; i < s.vector.Length (); ++i)
	result.vector [i] = s.vector [i] & t.vector [i];
    return result;
}

SetAsBitVector operator - (
    SetAsBitVector const& s, SetAsBitVector const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    SetAsBitVector result (s.universeSize);
    for (unsigned int i = 0; i < s.vector.Length (); ++i)
	result.vector [i] = s.vector [i] & ~t.vector [i];
    return result;
}
