//
//   This file contains the C++ code from Program 8.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm08_11.cpp
//
void ChainedHashTable::Insert (Object& object)
{
    array [H (object)].Append (&object);
    ++count;
}

void ChainedHashTable::Withdraw (Object& object)
{
    array [H (object)].Extract (&object);
    --count;
}
