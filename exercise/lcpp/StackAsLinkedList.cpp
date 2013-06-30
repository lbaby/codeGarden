//
//   This file contains the C++ code from Program 6.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_08.cpp
//

#include <StackAsLinkedList.h>

StackAsLinkedList::StackAsLinkedList () :
    list ()
    {}

void StackAsLinkedList::Purge ()
{
    if (IsOwner ())
    {
	ListElement<Object*> const* ptr;

	for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	    delete ptr->Datum ();
    }
    list.Purge ();
    count = 0;
}

StackAsLinkedList::~StackAsLinkedList ()
    { Purge (); }
    
    
    
    void StackAsLinkedList::Push (Object& object)
{
    list.Prepend (&object);
    ++count;
}

Object& StackAsLinkedList::Pop ()
{
    if (count == 0)
	throw domain_error ("stack is empty");
    Object& result = *list.First ();
    list.Extract (&result);
    --count;
    return result;
}

Object& StackAsLinkedList::Top () const
{
    if (count == 0)
	throw domain_error ("stack is empty");
    return *list.First ();
}
    
    
    void StackAsLinkedList::Accept (Visitor& visitor) const
{
    ListElement<Object*> const* ptr;

    for (ptr = list.Head ();
	ptr != 0 && !visitor.IsDone (); ptr = ptr->Next ())
    {
	visitor.Visit (*ptr->Datum ());
    }
}
    
    


StackAsLinkedList::Iter::Iter (
    StackAsLinkedList const& _stack) :
    stack (_stack)
    { Reset (); }

bool StackAsLinkedList::Iter::IsDone () const
    { return position == 0; }

Object& StackAsLinkedList::Iter::operator * () const
{
    if (position != 0)
	return *position->Datum ();
    else
	return NullObject::Instance ();
}

void StackAsLinkedList::Iter::operator ++ ()
{
    if (position != 0)
	position = position->Next ();
}

void StackAsLinkedList::Iter::Reset ()
    { position = stack.list.Head (); }
    

Iterator & StackAsLinkedList::NewIterator(void) const
{
	return *new Iter(*this);
}


