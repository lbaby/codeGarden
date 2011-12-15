//
//   This file contains the C++ code from Program 14.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_16.cpp
//
long int RandomNumberGenerator::seed = 1L;
long int const RandomNumberGenerator::a = 16807L;
long int const RandomNumberGenerator::m = 2147483647L;
long int const RandomNumberGenerator::q = 127773L;
long int const RandomNumberGenerator::r = 2836L;

void RandomNumberGenerator::SetSeed (long int s)
{
    if (s < 1 || s >= m)
	throw invalid_argument ("invalid seed");
    seed = s;
}

double RandomNumberGenerator::Next ()
{
    seed = a * (seed % q) - r * (seed / q);
    if (seed < 0) 
	seed += m;
    return (double) seed / (double) m;
}
