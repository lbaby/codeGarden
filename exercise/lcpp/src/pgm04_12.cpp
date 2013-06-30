//
//   This file contains the C++ code from Program 4.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_12.cpp
//
template <class T>
void LinkedList<T>::Purge ()
{
    while (head != 0)
    {
	ListElement<T>* const tmp = head;
	head = head->next;
	delete tmp;
    }
    tail = 0;
}

template <class T>
LinkedList<T>::~LinkedList ()
    { Purge (); }
