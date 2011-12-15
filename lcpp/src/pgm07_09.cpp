//
//   This file contains the C++ code from Program 7.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_09.cpp
//
void ListAsArray::Withdraw (Position const& arg)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == 0)
	throw domain_error ("list is empty");
    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");
    for (unsigned int i = position.offset; i < count-1U; ++i)
	array [i] = array [i + 1];
    --count;
}
