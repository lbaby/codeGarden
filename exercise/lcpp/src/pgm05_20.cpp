//
//   This file contains the C++ code from Program 5.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_20.cpp
//
Object& Association::Key () const
    { return *key; }

Object& Association::Value () const
{
    if (value == 0)
	return NullObject::Instance ();
    else
	return *value;
}

int Association::CompareTo (Object const& object) const
{
    Association const& association =
	dynamic_cast<Association const&> (object);
    return Key ().Compare (association.Key ());
}

void Association::Put (std::ostream& s) const
{
    s << "Association {" << *key;
    if (value != 0)
	s << ", " << *value;
    s << "}";
}
