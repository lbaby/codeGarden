//
//   This file contains the C++ code from Program 8.5 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_05.cpp
//
class HashingVisitor : public Visitor
{
    HashValue value;
public:
    HashingVisitor (HashValue _value) : value (_value)
	{}
    void Visit (Object& object)
	{ value += object.Hash (); }
    HashValue Value () const
	{ return value; }
};

HashValue Container::Hash () const
{
    HashingVisitor visitor (::Hash (typeid (*this).name ()));
    Accept (visitor);
    return visitor.Value ();
}
