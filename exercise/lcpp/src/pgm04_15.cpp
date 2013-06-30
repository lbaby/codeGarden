//
//   This file contains the C++ code from Program 4.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_15.cpp
//
template <class T>
void LinkedList<T>::Prepend (T const& item)
{
    ListElement<T>* const tmp = new ListElement<T> (item, head);
    if (head == 0)
	tail = tmp;
    head = tmp;
}
