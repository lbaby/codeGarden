//
//   This file contains the C++ code from Program 7.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_18.cpp
//
class Term : public Object
{
    double coefficient;
    unsigned int exponent;
public:
    Term (double, unsigned int);
    // ...
    int CompareTo (Object const&) const;
    void Differentiate ();
};

Term::Term (double _coefficient, unsigned int _exponent) :
    coefficient (_coefficient),
    exponent (_exponent)
    {}

int Term::CompareTo (Object const& object) const
{
    Term const& term = dynamic_cast<Term const&> (object);
    if (exponent == term.exponent)
	return ::Compare (coefficient, term.coefficient);
    else
	return exponent - term.exponent;
}

void Term::Differentiate ()
{
    if (exponent > 0)
    {
	coefficient *= exponent;
	exponent -= 1;
    }
    else
	coefficient = 0;
}
