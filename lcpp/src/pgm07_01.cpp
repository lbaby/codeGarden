//
//   This file contains the C++ code from Program 7.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_01.cpp
//
class Position : public Iterator
{
};

class List : public virtual SearchableContainer
{
public:
    virtual Object& operator [] (unsigned int) const = 0;
    virtual Object& operator [] (Position const&) const = 0;
    virtual Position& FindPosition (Object const&) const = 0;
    virtual void Withdraw (Position const&) = 0;
};

class OrderedList : public virtual List
{
public:
    virtual void InsertAfter (Position const&, Object&) = 0;
    virtual void InsertBefore (Position const&, Object&) = 0;
};
