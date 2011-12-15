//
//   This file contains the C++ code from Program 8.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_21.cpp
//
void OpenScatterTable::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("scatter table is empty");
    unsigned int const offset = FindInstance (object);
    if (offset == length)
	throw invalid_argument ("object not found");
    array [offset].state = Entry::deleted;
    array [offset].object = 0;
    --count;
}
