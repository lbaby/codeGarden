
//
//   This file contains the C++ code from Program 7.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_10.cpp
//
#ifndef LISTASLINKEDLIST_H_
#define LISTASLINKEDLIST_H_

#include <List.h>
#include <Object.h>
#include <Visitor.h>
#include <LinkedList.h>

class ListAsLinkedList : public virtual OrderedList
{
protected:
    LinkedList<Object*> linkedList;
    int CompareTo(Object const &o) const 
    {
     ListAsLinkedList  const &l = dynamic_cast< ListAsLinkedList  const & > (o);
     return (int)(count -  l.count);
    }
    

    class Pos;
public:
    ListAsLinkedList ();
    ~ListAsLinkedList ()
    {
    	Purge();
    }
    
   void Insert (Object& object);
    Object& operator [] (unsigned int offset) const;
    bool IsMember (Object const& object) const;
    Object& Find (Object const& object) const;
    void Withdraw (Object& object);
    void InsertAfter ( Position const& arg, Object& object);
    void Withdraw (Position const& arg);
    Position& FindPosition (Object const& object) const;
    Object& operator [] (Position const& arg) const;
    
    void Accept(Visitor&) const ;
    void InsertBefore (Position const& arg, Object& object);
    void Purge(void) ;
    
    friend class Pos;
};


class ListAsLinkedList::Pos : public Position
{
    ListAsLinkedList const& list;
    ListElement<Object*> const* element;
public:
    // ...
    
        Pos(ListAsLinkedList const& arg) : list(arg) , element(0) 
    {}
    
    Pos( ListAsLinkedList const& arg, ListElement<Object*> const* ele)
     : list(arg), element(ele)
     {}
     
    void Reset(void)
    {
    	element = 0;
    }
     
     bool IsDone(void) const
     {
     	return   (element );
     }
     
     void operator ++ (void)
     {
     	element = element->Next();
     }
     
    Object& operator*() const
    {
    	return * ( element->Datum() );
    }
    
    friend class ListAsLinkedList;
};


#endif /*LISTASLINKEDLIST_H_*/
