//
//   This file contains the C++ code from Program 5.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_09.cpp
//


#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <Object.h>
#include <Ownership.h>
#include <Iterator.h>
#include <Visitor.h>





class Container : public virtual Object, public virtual Ownership
{
protected:
    unsigned int count;

    Container ();
public:
    virtual unsigned int Count () const;
    virtual bool IsEmpty () const;
    virtual bool IsFull () const;
    virtual HashValue Hash () const;
    virtual void Put (std::ostream&) const;
    virtual Iterator& NewIterator () const;
    virtual void Purge () = 0;
    virtual void Accept (Visitor&) const = 0;
};

#endif
