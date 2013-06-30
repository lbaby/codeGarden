//
//   This file contains the C++ code from Program 7.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_02.cpp
//

#ifndef LISTASARRAY_H_
#define LISTASARRAY_H_

#include <List.h>
#include <Array.h>
#include <Object.h>
#include <Visitor.h>
#include <Iterator.h>



class ListAsArray : public virtual OrderedList
{
protected:
    Array<Object*> array;

    class Pos;
    int CompareTo(const Object& o) const
    {
    	ListAsArray const & l = dynamic_cast<ListAsArray const &>(o);
    	return (int) (count - l.count);
    }
    
public:
    ListAsArray (unsigned int);
    // ...
    void Insert (Object& object);
    Object& operator [] (unsigned int offset) const;
    bool IsMember (Object const& object) const;
    Object& Find (Object const& object) const;
    void Withdraw (Object& object);
    void InsertAfter ( Position const& arg, Object& object);
    void Withdraw (Position const& arg);
    Position& FindPosition (Object const& object) const;
    Object& operator [] (Position const& arg) const;
    
    Iterator & NewIterator(void) const;
    void Accept(Visitor&) const ;
    void InsertBefore (Position const& arg, Object& object);
    void Purge(void) ;
    
    ~ListAsArray()
    {
    	Purge();
    }

    
    friend class Pos;
};


class ListAsArray::Pos : public Position
{
protected:
    ListAsArray const& list;
    unsigned int offset;
public:
    // ...
    Pos( ListAsArray const& arg) : list(arg) , offset(0) 
    {}
    
    Pos( ListAsArray const& arg, unsigned int pos)
     : list(arg), offset(pos)
     {}
     
    void Reset(void)
    {
    	offset = 0;
    }
     
     bool IsDone(void) const
     {
     	return !  (offset  < list.count );
     }
     
     void operator ++ (void)
     {
     	++ offset;
     }
     
    Object& operator*() const
    {
    	return *list.array[offset];
    }
    
    friend class ListAsArray;
    friend class SortedListAsArray;
};

#endif /*LISTASARRAY_H_*/
