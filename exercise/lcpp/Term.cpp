//
//   This file contains the C++ code from Program 7.28 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_28.cpp
//
#include <Term.h>

#include <stdexcept>


double Term::Coefficient () const
    { return coefficient; }

unsigned int Term::Exponent () const
    { return exponent; }

Term operator + (Term const& arg1, Term const& arg2)
{
    if (arg1.exponent != arg2.exponent)
	throw std::domain_error ("unequal exponents");
    return Term (arg1.coefficient + arg2.coefficient,
	arg1.exponent);
}
