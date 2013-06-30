//
//   This file contains the C++ code from Program 5.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_19.cpp
//

#include <Association.h>
#include <NullObject.h>


Association::Association (Object& _key) :
    key (&_key),
    value (0)
    {}

Association::Association (Object& _key, Object& _value) :
    key (&_key),
    value (&_value)
    {}

Association::~Association ()
{
    if (IsOwner ())
    {
	delete key;
	delete value;
    }
}



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
    s << "}\n";
}

HashValue Association::Hash () const
{
	return key->Hash();
}
	
