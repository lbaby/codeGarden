#ifndef EVENT_H_
#define EVENT_H_
//
//   This file contains the C++ code from Program 11.21 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_21.cpp
//


#include <Association.h>
#include <Wrapper.h>

typedef double doub_time;

class Event : public Association
{
public:
    enum type
    {
	arrival, departure
    };
    typedef Wrapper<type> Type;
    typedef Wrapper<doub_time> Time;

    Event (type typ, doub_time tim) :
	Association (*new Time (tim), *new Type (typ)) {}
    Time& Key () const
	{ return dynamic_cast<Time&> (Association::Key ()); }
    Type& Value () const
	{ return dynamic_cast<Type&> (Association::Value()); }
};

#endif /*EVENT_H_*/
