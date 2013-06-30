//
//   This file contains the C++ code from Program A.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_04.cpp
//
Complex::Complex () :
    real (0), imag (0)
    {}

Complex::Complex (double x) :
    real (x), imag (0)
    {}

Complex::Complex (double x, double y) :
    real (x), imag (y)
    {}

Complex::Complex (Complex const& c) :
    real (c.real), imag (c.imag)
    {}

Complex::~Complex ()
    {}
