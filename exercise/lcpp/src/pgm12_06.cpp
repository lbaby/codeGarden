//
//   This file contains the C++ code from Program 12.6 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_06.cpp
//
class SetAsBitVector : public Set
{
    typedef unsigned int Word;
    enum { wordBits = bitsizeof (Word) };

    Array<Word> vector;
public:
    SetAsBitVector (unsigned int);
    // ...
};
