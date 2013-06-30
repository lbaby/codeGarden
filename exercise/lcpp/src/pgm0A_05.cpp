//
//   This file contains the C++ code from Program A.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_05.cpp
//
double Complex::Real () const
    { return real; }

double Complex::Imag () const
    { return imag; }

double Complex::R () const
    { return std::sqrt (real * real + imag * imag); }

double Complex::Theta () const
    { return atan2 (imag, real); }

void Complex::Put (std::ostream& s) const
    { s << real << "+" << imag << "i"; }
