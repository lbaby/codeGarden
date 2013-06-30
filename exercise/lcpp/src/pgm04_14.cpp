//
//   This file contains the C++ code from Program 4.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_14.cpp
//
template <class T>
T const& LinkedList<T>::First () const
{
    if (head == 0)
	throw domain_error ("list is empty");
    return head->datum;
}

template <class T>
T const& LinkedList<T>::Last () const
{
    if (tail == 0)
	throw domain_error ("list is empty");
    return tail->datum;
}
