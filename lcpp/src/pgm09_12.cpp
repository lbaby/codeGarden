//
//   This file contains the C++ code from Program 9.12 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_12.cpp
//
class NaryTree : public Tree
{
protected:
    Object* key;
    unsigned int const degree;
    Array<NaryTree*> subtree;
public:
    NaryTree (unsigned int);
    NaryTree (unsigned int, Object&);
    ~NaryTree ();

    Object& Key () const;
    NaryTree& Subtree (unsigned int) const;
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void AttachSubtree (unsigned int, NaryTree&);
    virtual NaryTree& DetachSubtree (unsigned int);
    // ...
};
