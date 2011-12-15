
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

#ifndef NARYTREE_H_
#define NARYTREE_H_

#include <Tree.h>
#include <Object.h>
#include <Array.h>


class NaryTree : public Tree
{
protected:
    Object* key;
    int  CompareTo(const Object& o) const
    {
    	const NaryTree &nt = dynamic_cast<const NaryTree &>(o);
    	
    	return (int)(degree - nt.degree);
    }
    
    
    unsigned int const degree;
    Array<NaryTree*> subtree;
public:
    NaryTree (unsigned int);
    NaryTree (unsigned int, Object&);
    ~NaryTree ()
    {
    	Purge();
    }
    
    void Purge();

    Object& Key () const;
    NaryTree& Subtree (unsigned int) const;
    virtual void AttachKey (Object&);
    virtual Object& DetachKey ();
    virtual void AttachSubtree (unsigned int, NaryTree&);
    virtual NaryTree& DetachSubtree (unsigned int);
    bool IsEmpty () const;
     
     bool IsLeaf () const
     {
     	return subtree[0]->IsEmpty() && key;
     }
     
     unsigned  int Degree() const
     {
     	return degree;
     }
     
    // ...
};
#endif /*NARYTREE_H_*/
