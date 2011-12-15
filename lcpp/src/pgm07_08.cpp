//
//   This file contains the C++ code from Program 7.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_08.cpp
//
void ListAsArray::InsertAfter (
    Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == array.Length ())
	throw domain_error ("list is full");
    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");

    unsigned int const insertPosition = position.offset + 1;

    for (unsigned int i = count; i > insertPosition; --i)
	array [i] = array [i - 1U];
    array [insertPosition] = &object;
    ++count;
}
