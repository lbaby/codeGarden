//
//   This file contains the C++ code from Program 6.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_02.cpp
//
class StackAsArray : public Stack
{
    Array<Object*> array;

    class Iter;
public:
    StackAsArray (unsigned int);
    // ...
    friend class Iter;
};

class StackAsArray::Iter : public Iterator
{
    StackAsArray const& stack;
    unsigned int position;
public:
    Iter (StackAsArray const&);
    // ...
};
