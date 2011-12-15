//
//   This file contains the C++ code from Program 5.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_12.cpp
//
#include <typeinfo>

class PuttingVisitor : public Visitor
{
    std::ostream& stream;
    bool comma;
public:
    PuttingVisitor (std::ostream& s) : stream (s), comma (false)
	{}
    void Visit (Object& object)
    {
	if (comma)
	    stream << ", ";
	stream << object;
	comma = true;
    }
};

void Container::Put (std::ostream& s) const
{
    PuttingVisitor visitor (s);

    s << typeid (*this).name () << " {";
    Accept (visitor);
    s << "}";
}
