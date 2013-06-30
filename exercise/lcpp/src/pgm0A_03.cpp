//
//   This file contains the C++ code from Program A.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm0A_03.cpp
//
class Complex
{
    double real;
    double imag;
public:
    Complex ();
    Complex (double);
    Complex (double, double);
    Complex (Complex const&);
    ~Complex ();

    double Real () const;
    double Imag () const;
    double R () const;
    double Theta () const;
    void Put (std::ostream&) const;

    void SetReal (double);
    void SetImag (double);
    Complex& operator = (Complex  const&);
};
