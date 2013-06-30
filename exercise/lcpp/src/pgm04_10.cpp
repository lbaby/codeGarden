//
//   This file contains the C++ code from Program 4.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_10.cpp
//
template <class T>
ListElement<T>::ListElement (
    T const& _datum, ListElement<T>* _next) :
    datum (_datum), next (_next)
    {}

template <class T>
T const& ListElement<T>::Datum () const
    { return datum; }

template <class T>
ListElement<T> const* ListElement<T>::Next () const
    { return next; }
