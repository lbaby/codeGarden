//
//   This file contains the C++ code from Program 6.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_15.cpp
//

#include <QueueAsArray.h>
#include <Object.h>
#include <stdexcept>
#include <HashingVisitor.h>



QueueAsArray::QueueAsArray (unsigned int size) :
    array (size),
    head (0),
    tail (size - 1U)
    {}

    int QueueAsArray::CompareTo(const Object &arg) const
    {
		QueueAsArray const & d = dynamic_cast<QueueAsArray const & >(arg);
		
		if(count != d.count){
			return (int)  (count - d.count);
		}else{
			for(unsigned int i = 0 ; i < count ; i++){
				if( *array[i] > *d.array[i]){
					return 1;
				}else if(  *array[i] < *d.array[i]){
					return -1;
				}
			}
			return 0;
		}
    }
    
void QueueAsArray::Purge ()
{
    if (IsOwner ())
    {
	for (unsigned int i = 0; i < count; ++i)
	{
	    delete array [head];
	    if (++head == array.Length ())
		head = 0;
	}
    }
    count = 0;
}

QueueAsArray::~QueueAsArray ()
    { Purge (); }

    
 
 Object& QueueAsArray::Head () const
{
    if (count == 0)
	throw std::domain_error ("queue is empty");
    return *array [head];
}

void QueueAsArray::Enqueue (Object& object)
{
    if (count == array.Length ())
	throw std::domain_error ("queue is full");
    if (++tail == array.Length ())
	tail = 0;
    array [tail] = &object;
    ++count;
}

Object& QueueAsArray::Dequeue ()
{
    if (count == 0)
	throw std::domain_error ("queue is empty");
    Object& result = *array [head];
    if (++head == array.Length ())
	head = 0;
    --count;
    return result;
}


void QueueAsArray::Accept (Visitor& visitor) const
{
    for (unsigned int i = 0;
	i < count && !visitor.IsDone (); ++i)
    {
	visitor.Visit (* (array [ ( i + head) % array.Length() ]));
    }
}



