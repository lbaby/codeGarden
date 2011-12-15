//
//   This file contains the C++ code from Program 5.2 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm05_02.cpp
//
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
