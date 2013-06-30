//
//   This file contains the C++ code from Program 12.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_05.cpp
//
bool operator == (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    for (unsigned int item = 0; item < s.universeSize; ++item)
	if (s.array [item] != t.array [item])
	    return false;
    return true;
}

bool operator <= (SetAsArray const& s, SetAsArray const& t)
{
    if (s.universeSize != t.universeSize)
	throw invalid_argument ("mismatched sets");
    for (unsigned int item = 0; item < s.universeSize; ++item)
	if (s.array [item] && !t.array [item])
	    return false;
    return true;
}
