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

#ifndef _STACKASARRAY_H_
#define _STACKASARRAY_H_

#include <Object.h>
#include <Stack.h>
#include <Array.h>
#include <Iterator.h>
#include <Wrapper.h>
#include <Container.h>
#include <NullIterator.h>
#include <NullObject.h>






class StackAsArray : public Stack
{
    Array<Object*> array;

     int CompareTo(const Object &ot) const {
     	return array.Length() - dynamic_cast<const StackAsArray&> (ot).array.Length();
     }
     
         class Iter;

public:


    StackAsArray (unsigned int);
    
    Iterator  & NewIterator(void) const;
    
    ~StackAsArray ();
     
 virtual int Compare(const Object &ot) const {
     	return CompareTo(ot);
     }
     
     void Push(Object&);
     Object& Pop (void);
     Object& Top() const;
     
         void Accept(Visitor&) const;
     
    void Purge();
    friend class Iter;
};

class StackAsArray::Iter : public Iterator
{
    StackAsArray const& stack;
    unsigned int position;
public:
   Iter();
    Iter (StackAsArray const&);
    	Object&  operator * () const;
    	void operator ++ ();
    	void Reset ();
    	bool IsDone() const;

};

#endif
