
//
//   This file contains the C++ code from Program 6.23 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm06_23.cpp
//

#ifndef DEQUEUEASARRAY_H_
#define DEQUEUEASARRAY_H_

#include <Deque.h>
#include <QueueAsArray.h>

class DequeAsArray :  public QueueAsArray ,public  Deque
{
	int CompareTo(const Object& arg) const 
	{
		return QueueAsArray::CompareTo(arg);
	}
	
public:
    DequeAsArray (unsigned int len)  : QueueAsArray(len)
    {
    }
    Object& Head () const;
    void EnqueueTail (Object& object);
    Object& DequeueHead ();
    Object& Tail () const;
    void EnqueueHead (Object& object);
    Object& DequeueTail ();
    void Accept (Visitor& visitor) const;
    HashValue Hash(void) const 
    {
    	return Container::Hash();
    }
    // ...
};


#endif /*DEQUEUEASARRAY_H_*/
