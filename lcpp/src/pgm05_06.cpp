//
//   This file contains the C++ code from Program 5.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_06.cpp
//
template <class T>
class Wrapper : public Object
{
protected:
    T datum;

    int CompareTo (Object const&) const;
public:
    Wrapper ();
    Wrapper (T const&);
    Wrapper& operator = (T const&);
    operator T const& () const;
    HashValue Hash () const;
    void Put (std::ostream&) const;
};
