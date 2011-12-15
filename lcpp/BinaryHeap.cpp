
//
//   This file contains the C++ code from Program 11.3 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_03.cpp
//

#include <BinaryHeap.h>
#include <Array.h>

#include <stdexcept>



BinaryHeap::BinaryHeap (unsigned int length) :
    array (length, 1)
    {}

void BinaryHeap::Accept(Visitor& v) const
{
	for(unsigned int i  = 1 ; ( i < count +1) && !v.IsDone()   ; i++){
		v.Visit(*array[i]);
	}
}
    int BinaryHeap::CompareTo(const Object& object) const
    {
    	const BinaryHeap & bh= dynamic_cast<const  BinaryHeap & >(object);
    	
    	if(count  == bh.count){
    		for(unsigned int i = 1; i < count +1 ; i++){
    			if( *array[i] != *bh.array[i] ){
    				return array[i]->Compare( *bh.array[i]);
    			}
    		}
    			
    			return 0;
    			
    	}else{
    		return (int)(count - bh.count);
    	}
    		
    }


void BinaryHeap::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 1; i < count + 1; ++i)
	    delete array [i];
    }
    count = 0;
}

BinaryHeap::~BinaryHeap ()
    { Purge (); }
    
 
 
void BinaryHeap::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw std::domain_error ("priority queue is full");
    ++count;
    unsigned int i = count;
    while (i > 1 && *array [i / 2] > object)
    {
	array [i] = array [i / 2];
	i /= 2;
    }
    array [i] = &object;
}


Object& BinaryHeap::FindMin () const
{
    if (count == 0)
	throw std::domain_error ("priority queue is empty");
    return *array [1];
}


Object& BinaryHeap::DequeueMin ()
{
    if (count == 0)
	throw std::domain_error ("priority queue is empty");
    Object& result = *array [1];
    Object& last = *array [count];
    --count;
    unsigned int i = 1;
    while (2 * i < count + 1)
    {
	unsigned int child = 2 * i;
	if (child + 1 < count + 1
	    && *array [child + 1] < *array [child])
	    child += 1;
	if (last <= *array [child])
	    break;
	array [i] = array [child];
	i = child;
    }
    array [i] = &last;
    return result;
}




