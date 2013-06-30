//
//   This file contains the C++ code from Program 4.19 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_19.cpp
//
template <class T>
void LinkedList<T>::InsertAfter (
    ListElement<T> const* arg, T const& item)
{
    ListElement<T>* ptr = const_cast<ListElement<T>*> (arg);
    if (ptr == 0)
	throw invalid_argument ("invalid position");
    ListElement<T>* const tmp =
	new ListElement<T> (item, ptr->next);
    ptr->next = tmp;
    if (tail == ptr)
	tail = tmp;
}

template <class T>
void LinkedList<T>::InsertBefore (
    ListElement<T> const* arg, T const& item)
{
    ListElement<T>* ptr = const_cast<ListElement<T>*> (arg);
    if (ptr == 0)
	throw invalid_argument ("invalid position");
    ListElement<T>* const tmp = new ListElement<T> (item, ptr);
    if (head == ptr)
	head = tmp;
    else
    {
	ListElement<T>* prevPtr = head;
	while (prevPtr != 0 && prevPtr->next != ptr)
	    prevPtr = prevPtr->next;
	if (prevPtr == 0)
	    throw invalid_argument ("invalid position");
	prevPtr->next = tmp;
    }
}
