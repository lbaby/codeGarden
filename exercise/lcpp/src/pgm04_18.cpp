//
//   This file contains the C++ code from Program 4.18 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm04_18.cpp
//
template <class T>
void LinkedList<T>::Extract (T const& item)
{
    ListElement<T>* ptr = head;
    ListElement<T>* prevPtr = 0;
    while (ptr != 0 && ptr->datum != item)
    {
	prevPtr = ptr;
	ptr = ptr->next;
    }
    if (ptr == 0)
	throw invalid_argument ("item not found");
    if (ptr == head)
	head = ptr->next;
    else
	prevPtr->next = ptr->next;
    if (ptr == tail)
	tail = prevPtr;
    delete ptr;
}
