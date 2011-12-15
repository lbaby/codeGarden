//
//   This file contains the C++ code from Program 4.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_13.cpp
//
template <class T>
ListElement<T> const* LinkedList<T>::Head () const
    { return head; }

template <class T>
ListElement<T> const* LinkedList<T>::Tail () const
    { return tail; }

template <class T>
bool LinkedList<T>::IsEmpty () const
    { return head == 0; }
