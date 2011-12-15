//
//   This file contains the C++ code from Program 5.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_10.cpp

//



#include <Container.h>
#include <Visitor.h>
#include <NullIterator.h>
#include <PuttingVisitor.h>
#include <typeinfo>
#include <HashingVisitor.h>




void Container::Put (std::ostream& s) const
{
    PuttingVisitor visitor (s);

    s << typeid (*this).name () << " {";
    Accept (visitor);
    s << "}";
}


Iterator & Container::NewIterator(void) const
{
	return *new NullIterator;
}

Container::Container () :
    count (0)
    {}

unsigned int Container::Count () const
    { return count; }

bool Container::IsEmpty () const
    { return Count () == 0; }

bool Container::IsFull () const
    { return false; }


HashValue Container::Hash () const
{
    HashingVisitor visitor (::Hash (typeid (*this).name ()));
    Accept (visitor);
    return visitor.Value ();
}

