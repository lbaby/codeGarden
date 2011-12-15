#ifndef SETASARRAY_H_
#define SETASARRAY_H_
//
//   This file contains the C++ code from Program 12.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm12_02.cpp
//
#include <Array.h>
#include <Set.h>

class SetAsArray : public Set
{
    Array<bool> array;
public:
    SetAsArray (unsigned int);
    void SetAsArray::Insert (Object& object);
    bool SetAsArray::IsMember (Object const& object) const;
    void SetAsArray::Withdraw (Object& object);
    
    friend SetAsArray operator + (
	SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator - (
	SetAsArray const&, SetAsArray const&);
    friend SetAsArray operator * (
	SetAsArray const&, SetAsArray const&);
    friend bool operator == (
	SetAsArray const&, SetAsArray const&);
    friend bool operator <= (
	SetAsArray const&, SetAsArray const&);
};

#endif /*SETASARRAY_H_*/
