//
//   This file contains the C++ code from Program 13.15 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm13_15.cpp
//
typedef unsigned int time;

class Event : public Association
{
public:
    typedef Wrapper<time> Time;
    typedef Wrapper<void*> VoidPtr;

    Event (time t, void* ptr) :
	Association (*new Time (t), *new VoidPtr (ptr)) {}
    Time& Key () const
	{ return dynamic_cast<Time&> (Association::Key ()); }
    VoidPtr& Value () const
	{ return dynamic_cast<VoidPtr&> (Association::Value()); }
};
