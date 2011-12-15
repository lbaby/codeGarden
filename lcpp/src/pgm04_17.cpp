//
//   This file contains the C++ code from Program 4.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_17.cpp
//
template <class T>
LinkedList<T>::LinkedList (LinkedList<T> const& linkedList) :
    head (0),
    tail (0)
{
    ListElement<T> const* ptr;
    for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
	Append (ptr->datum);
}

template <class T>
LinkedList<T>& LinkedList<T>::operator = (
    LinkedList<T> const& linkedList)
{
    if (&linkedList != this)
    {
	Purge ();
	ListElement<T> const* ptr;
	for (ptr = linkedList.head; ptr != 0; ptr = ptr->next)
	    Append (ptr->datum);
    }
    return *this;
}
