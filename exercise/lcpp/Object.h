//
//   This file contains the C++ code from Program 5.1 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_01.cpp
//


#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <Hash.h>

#include <ostream>
#include <typeinfo>
#include <stdlib.h>




#ifdef DPRINT
	#include <iostream>
#endif

class Object
{
protected:
    virtual int CompareTo (Object const&) const = 0;
public:
    virtual ~Object ();
    virtual bool IsNull () const;
    virtual int Compare (Object const&) const;
    virtual HashValue Hash () const = 0;
    virtual void Put (std::ostream&) const = 0;
};

inline bool operator == (Object const& left, Object const& right)
    { return left.Compare (right) == 0; }

inline bool operator != (Object const& left, Object const& right)
    { return left.Compare (right) != 0; }

inline bool operator <= (Object const& left, Object const& right)
    { return left.Compare (right) <= 0; }

inline bool operator <  (Object const& left, Object const& right)
    { return left.Compare (right) <  0; }

inline bool operator >= (Object const& left, Object const& right)
    { return left.Compare (right) >= 0; }

inline bool operator >  (Object const& left, Object const& right)
    { return left.Compare (right) >  0; }

inline std::ostream& operator << (std::ostream& s, Object const& object)
    { object.Put (s); return s; }


template <typename T> 
int Compare(T l, T r)
{
	if ( l > r ){
		return 1;
	}else if (l == r) {
		return 0;
	}else {
		return -1;
	}
}





#endif

