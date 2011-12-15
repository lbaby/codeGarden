//
//   This file contains the C++ code from Program 8.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_03.cpp
//
unsigned int const shift = 6;
HashValue const mask = ~0U << (bitsizeof (HashValue) - shift);

HashValue Hash (std::string const& s)
{
    HashValue result = 0;
    for (unsigned int i = 0; s [i] != 0; ++i)
	result = (result & mask) ^ (result << shift) ^ s [i];
    return result;
}
