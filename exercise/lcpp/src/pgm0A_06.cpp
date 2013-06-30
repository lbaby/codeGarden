//
//   This file contains the C++ code from Program A.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_06.cpp
//
void Complex::SetReal (double x)
    { real = x; }

void Complex::SetImag (double y)
    { imag = y; }

Complex& Complex::operator = (Complex  const& c)
{
    real = c.real;
    imag = c.imag;
    return *this;
}
