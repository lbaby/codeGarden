//
//   This file contains the C++ code from Program 7.11 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_11.cpp
//

#include <Object.h>
#include <ListAsLinkedList.h>
#include <NullObject.h>
#include <stdexcept>
#include <Visitor.h>


using std::out_of_range;
using std::logic_error;


ListAsLinkedList::ListAsLinkedList () :
    linkedList ()
    {}

void ListAsLinkedList::Insert (Object& object)
{
    linkedList.Append (&object);
    ++count;
}

Object& ListAsLinkedList::operator [] (unsigned int offset) const
{
    if (offset >= count)
	throw out_of_range ("invalid offset");

    unsigned int i = 0;
    ListElement<Object*> const* ptr =
	linkedList.Head ();
    while (i < offset && ptr != 0)
    {
	ptr = ptr->Next ();
	++i;
    }
    if (ptr == 0)
	throw logic_error ("should never happen");
    return *ptr->Datum ();
}

bool ListAsLinkedList::IsMember (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = linkedList.Head (); ptr != 0; ptr = ptr->Next ())
	if (ptr->Datum () == &object)
	    return true;
    return false;
}

Object& ListAsLinkedList::Find (Object const& object) const
{
    ListElement<Object*> const* ptr;

    for (ptr = linkedList.Head (); ptr != 0; ptr = ptr->Next ())
	if (*ptr->Datum () == object)
	    return *ptr->Datum ();
    return NullObject::Instance ();
}



void ListAsLinkedList::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");
    linkedList.Extract (&object);
    --count;
}


Position& ListAsLinkedList::FindPosition (
    Object const& object) const
{
    ListElement<Object*> const* ptr =
	linkedList.Head ();
    while (ptr != 0 && *ptr->Datum () != object)
	ptr = ptr->Next ();
    return *new Pos (*this, ptr);
}

Object& ListAsLinkedList::operator [] (
    Position const& arg) const
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");
    return *position.element->Datum ();
}


void ListAsLinkedList::InsertAfter (
    Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");
    linkedList.InsertAfter (position.element, &object);
    ++count;
}

void ListAsLinkedList::Withdraw (Position const& arg)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == 0)
	throw domain_error ("list is empty");
    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");

    linkedList.Extract (position.element->Datum ());
    --count;
}

void ListAsLinkedList::Purge()
{
	if(IsOwner()){
		ListElement<Object*> const* ptr;
		for (ptr = linkedList.Head (); ptr != 0 ; ptr = ptr->Next ()){
			delete ptr->Datum();
		}
	}
	
	count = 0;
    	
}


void ListAsLinkedList::Accept(Visitor & visitor ) const 
{

		ListElement<Object*> const* ptr;
		for (ptr = linkedList.Head (); ptr != 0  && !visitor.IsDone() ; ptr = ptr->Next ()){
			visitor.Visit( * ( ptr-> Datum() )   );
		}
	
}


void ListAsLinkedList::InsertBefore (
    Position const& arg, Object& object)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (&position.list != this || position.element == 0)
	throw invalid_argument ("invalid position");
    linkedList.InsertBefore (position.element, &object);
    ++count;
}

