//
//   This file contains the C++ code from Program 4.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_16.cpp
//
template <class T>
void LinkedList<T>::Append (T const& item)
{
    ListElement<T>* const tmp = new ListElement<T> (item, 0);
    if (head == 0)
	head = tmp;
    else
	tail->next = tmp;
    tail = tmp;
}
