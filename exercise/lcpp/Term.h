
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

#ifndef TERM_H_
#define TERM_H_

#include <Object.h>


class Term : public Object
{
    double coefficient;
    unsigned int exponent;
    int CompareTo(const Object & arg) const
    {
    	Term const & term = dynamic_cast<Term const &> ( arg);
    	
    	return exponent  - term.exponent;
    }
public:
    // ...
    Term(double coe, unsigned int exp): coefficient(coe), exponent(exp)
    {}
    	
    HashValue Hash(void) const 
    {
    	return exponent;
    }
   void  Put(std::ostream& o) const
   {
   	o<<"Term: coefficient^exponent  == "<<coefficient << "^" << exponent << '\n';
   }
   	
    double  Coefficient () const;
    unsigned int Exponent () const;
    friend Term operator + (Term const&, Term const&);
};

#endif /*TERM_H_*/
