//
//   This file contains the C++ code from Program 7.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm07_03.cpp
//

#include <ListAsArray.h>
#include <Object.h>
#include <NullObject.h>

#ifdef DPRINT 
	#include <iostream>
#endif


#include <stdexcept>

using std::domain_error;
using std::out_of_range;
using std::invalid_argument;


ListAsArray::ListAsArray (unsigned int size) :
    array (size)
    {}

void ListAsArray::Insert (Object& object)
{
    if (count == array.Length ())
	throw domain_error ("list is full");
    array [count] = &object;
    ++count;
}

Object& ListAsArray::operator [] (unsigned int offset) const
{
    if (offset >= count)
	throw out_of_range ("invalid offset");
    return *array [offset];
}

bool ListAsArray::IsMember (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
	if (array [i] == &object)
	    return true;
    return false;
}

Object& ListAsArray::Find (Object const& object) const
{
    for (unsigned int i = 0; i < count; ++i)
	if (*array [i] == object)
	    return *array [i];
    return NullObject::Instance ();
}

void ListAsArray::Withdraw (Object& object)
{
    if (count == 0)
	throw domain_error ("list is empty");
    unsigned int i = 0;
    while (i < count && array [i] != &object)
	++i;
    if (i == count)
	throw invalid_argument ("object not found");

    for ( ; i < count - 1U; ++i)
	array [i] = array [i + 1];
    --count;
}


void ListAsArray::InsertAfter (
    Position const& arg, Object& object)
{


    Pos const& position = dynamic_cast<Pos const&> (arg);

    #ifdef DPRINT
       std:: cerr<< " obj "<< object<<" insertAfter:  pos.offset = " << position.offset <<std::endl;
     #endif
    if (count == array.Length ())
	throw domain_error ("list is full");
    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");

    unsigned int const insertPosition = position.offset + 1 ;

        
    
    for (unsigned int i = count; i > insertPosition; --i)
	array [i] = array [i - 1U];
    array [insertPosition] = &object;
    ++count;
}


void ListAsArray::Withdraw (Position const& arg)
{
    Pos const& position = dynamic_cast<Pos const&> (arg);

    if (count == 0)
	throw domain_error ("list is empty");
    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");
    for (unsigned int i = position.offset; i < count-1U; ++i)
	array [i] = array [i + 1];
    --count;
}


Position& ListAsArray::FindPosition (Object const& object) const
{
    unsigned int i = 0;
    while (i < count && *array [i] != object)
	++i;
    return *new Pos (*this, i);
}

Object& ListAsArray::operator [] (Position const& arg) const
{
    Pos const& position = dynamic_cast<Pos const&> (arg);
    #ifdef DPRINT
    std::cerr<< "pos @ operator [] (pos) : " << position.offset << std::endl;
    #endif
    if (&position.list != this || position.offset >= count)
	throw invalid_argument ("invalid position");
    return *array [position.offset];
}

void ListAsArray::Purge(void)
    {
    	if(IsOwner ()){
    		for( unsigned int i = 0 ; i < count; i ++){
    			#ifdef DPRINT
    			std::cerr<<" ListAsArray : deleting  array["<<i<<"]@count="<<count<<std::endl;
    			#endif 
    			delete array[i];
    		}
    	}
    	
    	count = 0;
    }
    
 void ListAsArray::InsertBefore (
    Position const& arg, Object& object)
{

    Pos const& position = dynamic_cast<Pos const&> (arg);

    #ifdef DPRINT
       std:: cerr<< " obj "<< object<<" insertBefore:  pos.offset = " << position.offset <<std::endl;
     #endif
     
    if (count == array.Length ())
	throw domain_error ("list is full");
    if (&position.list != this  || position.offset  >= count+1 )
	throw invalid_argument ("invalid position");

    unsigned int  insertPosition =
    	  position.offset   ;

    for (unsigned int i = count; i > insertPosition; --i)
	array [i] = array [i - 1U];
    array [insertPosition] = &object;
    ++count;
}


void ListAsArray::Accept(Visitor& visitor)  const 
{
	for(unsigned int i = 0 ; i < count ; ++i){
		visitor.Visit(*array[i]);
	}
	
}

    Iterator & ListAsArray::NewIterator(void) const
    {
    	return *new Pos(*this, 0 );
    }
 
