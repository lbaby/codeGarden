//
//   This file contains the C++ code from Program 12.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_12.cpp
//
MultisetAsArray operator + (
    MultisetAsArray const& s, MultisetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    MultisetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	result.array [i] = s.array [i] + t.array [i];
    return result;
}

MultisetAsArray operator * (
    MultisetAsArray const& s, MultisetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    MultisetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	result.array [i] = Min (s.array [i], t.array [i]);
    return result;
}

MultisetAsArray operator - (
    MultisetAsArray const& s, MultisetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    MultisetAsArray result (s.universeSize);
    for (unsigned int i = 0; i < s.universeSize; ++i)
	if (t.array [i] <= s.array [i])
	    result.array [i] = s.array [i] - t.array [i];
    return result;
}
