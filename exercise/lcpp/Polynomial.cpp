//
//   This file contains the C++ code from Program 7.30 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_30.cpp
//

#include <Polynomial.h>
#include <Term.h>

Polynomial operator + (
    Polynomial const& arg1, Polynomial const& arg2)
{
    Polynomial result;
    Iterator& pos1 = arg1.NewIterator ();
    Iterator& pos2 = arg2.NewIterator ();
    while (!pos1.IsDone () && !pos2.IsDone ())
    {
	Term const& term1 = dynamic_cast<Term const&> (*pos1);
	Term const& term2 = dynamic_cast<Term const&> (*pos2);
	if (term1.Exponent () < term2.Exponent ())
	{
	    result.Insert (*new Term (term1));
	    ++pos1;
	}
	else if (term1.Exponent () > term2.Exponent ())
	{
	    result.Insert (*new Term (term2));
	    ++pos2;
	}
	else
	{
	    Term sum = term1 + term2;
	    if (sum.Coefficient () != 0)
		result.Insert (*new Term (sum));
	    ++pos1;
	    ++pos2;
	}
    }
    while (!pos1.IsDone ())
    {
	Term const& term1 = dynamic_cast<Term const&> (*pos1);
	result.Insert (*new Term (term1));
	++pos1;
    }
    while (!pos2.IsDone ())
    {
	Term const& term2 = dynamic_cast<Term const&> (*pos2);
	result.Insert (*new Term (term2));
	++pos2;
    }
    delete &pos1;
    delete &pos2;
    return result;
}
