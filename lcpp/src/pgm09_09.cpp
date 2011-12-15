//
//   This file contains the C++ code from Program 9.9 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_09.cpp
//
class GeneralTree : public Tree
{
protected:
    Object* key;
    unsigned int degree;
    LinkedList<GeneralTree*> list;
public:
    GeneralTree (Object&);
    ~GeneralTree ();

    Object& Key () const;
    GeneralTree& Subtree (unsigned int) const;
    virtual void AttachSubtree (GeneralTree&);
    virtual GeneralTree& DetachSubtree (GeneralTree&);
    // ...
};
