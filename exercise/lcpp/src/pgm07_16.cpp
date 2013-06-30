//
//   This file contains the C++ code from Program 7.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_16.cpp
//
void ListAsLinkedList::InsertAfter (
    Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");
    linkedList.InsertAfter (position.element, &object);
    ++count;
}
