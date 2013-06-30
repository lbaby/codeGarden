
//
//   This file contains the C++ code from Program 6.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_07.cpp
//
#ifndef STACKASLINKEDLIST_H_
#define STACKASLINKEDLIST_H_

#include <Object.h>
#include <Stack.h>
#include <Container.h>
#include <LinkedList.h>
#include <Iterator.h>
#include <NullObject.h>
#include <NullIterator.h>



class StackAsLinkedList : public Stack
{
    LinkedList<Object*> list;
    int CompareTo(const Object & o) const{
    	return 0;
    }

    class Iter;
public:
    StackAsLinkedList ();

    
    Iterator  & NewIterator(void) const;
    
    ~StackAsLinkedList ();
     

     void Push(Object&);
     Object& Pop (void);
     Object& Top() const;
     
         void Accept(Visitor&) const;
     
    void Purge();
    friend class Iter;
};

class StackAsLinkedList::Iter : public Iterator
{
    StackAsLinkedList const& stack;
    ListElement<Object*> const* position;
public:
    Iter (StackAsLinkedList const&);
    	Object&  operator * () const;
    	void operator ++ ();
    	void Reset ();
    	bool IsDone() const;
    // ...
};


#endif /*STACKASLINKEDLIST_H_*/
