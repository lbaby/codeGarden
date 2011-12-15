//
//   This file contains the C++ code from Program 14.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_15.cpp
//
class RandomNumberGenerator
{
private:
    static long int seed;
    static long int const a;
    static long int const m;
    static long int const q;
    static long int const r;
public:
    static void SetSeed (long int);
    static double Next ();
};
