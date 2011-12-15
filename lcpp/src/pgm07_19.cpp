//
//   This file contains the C++ code from Program 7.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_19.cpp
//
class Polynomial : public ListAsLinkedList
{
public:
    void Differentiate ();
};

class DifferentiatingVisitor : public Visitor
{
public:
    void Visit (Object& object)
    {
	Term& term = dynamic_cast<Term&> (object);
	term.Differentiate ();
    }
};

void Polynomial::Differentiate ()
{
    DifferentiatingVisitor visitor;
    Accept (visitor);
    Object& zeroTerm = Find (Term (0, 0));
    if (!zeroTerm.IsNull ())
    {
	Withdraw (zeroTerm);
	delete &zeroTerm;
    }
}
