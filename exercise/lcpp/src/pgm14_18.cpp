//
//   This file contains the C++ code from Program 14.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm14_18.cpp
//
double SimpleRV::Sample ()
    { return RandomNumberGenerator::Next (); }

double UniformRV::Sample ()
    { return u + (v - u) * RandomNumberGenerator::Next (); }

double ExponentialRV::Sample ()
    { return -mu * std::log (RandomNumberGenerator::Next ()); }
