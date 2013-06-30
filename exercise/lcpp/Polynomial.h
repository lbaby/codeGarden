
//
//   This file contains the C++ code from Program 7.29 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_29.cpp
//


#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <SortedListAsArray.h>
#include <Term.h>



class Polynomial : public SortedListAsArray
{
public:
Polynomial(unsigned int n = 100):  ListAsArray(n), SortedListAsArray(n)
{}

Polynomial(const Polynomial & o) :ListAsArray(o.array.Length()), SortedListAsArray(o.array.Length())
{
	array = o.array;
	count = o.count;
	RescindOwnership ();
}

    // ...
    friend Polynomial operator + (
	Polynomial const&, Polynomial const&);
};

#endif /*POLYNOMIAL_H_*/
