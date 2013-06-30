//
//   This file contains the C++ code from Program 5.4 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_04.cpp
//
class NullObject : public Object
{
    static NullObject instance;

    NullObject ();
protected:
    int CompareTo (Object const&) const;
public:
    bool IsNull () const;
    HashValue Hash () const;
    void Put (std::ostream& s) const;

    static NullObject& Instance ();
};
