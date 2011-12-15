//
//   This file contains the C++ code from Program 5.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_07.cpp
//
template <class T>
Wrapper<T>::Wrapper () :
    datum ()
    {}

template <class T>
Wrapper<T>::Wrapper (T const& d) :
    datum (d)
    {}

template <class T>
Wrapper<T>& Wrapper<T>::operator = (T const& d)
{
    datum = d;
    return *this;
}

template <class T>
Wrapper<T>::operator T const& () const
    { return datum; }

template <class T>
int Wrapper<T>::CompareTo (Object const& obj) const
{
    Wrapper<T> const& arg =
	dynamic_cast<Wrapper<T> const&> (obj);
    return ::Compare (datum, arg.datum);
}

template <class T>
void Wrapper<T>::Put (std::ostream& s) const
    { s << datum; }
