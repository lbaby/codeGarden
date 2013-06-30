//
//   This file contains the C++ code from Program 7.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_07.cpp
//
Position& ListAsArray::FindPosition (Object const& object) const
{
    unsigned int i = 0;
    while (i < count && *array [i] != object)
	++i;
    return *new Pos (*this, i);
}

Object& ListAsArray::operator [] (Position const& arg) const
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");
    return *array [position.offset];
}
