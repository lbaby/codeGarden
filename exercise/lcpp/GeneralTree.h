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

#ifndef GENERALTREE_H_
#define GENERALTREE_H_

#include <Object.h>
#include <LinkedList.h>
#include <Tree.h>

class GeneralTree : public Tree
{
protected:
int CompareTo(const Object& o) const
{
	const GeneralTree &gt = 
	dynamic_cast<const GeneralTree &> (o);
	
	return (int)  (degree  - gt.degree);
}
 
	
    Object* key;
    unsigned int degree;
    LinkedList<GeneralTree*> list;
public:
    GeneralTree (Object&);
    ~GeneralTree ();
    
     bool IsEmpty () const
     {
     	return !key;
     }
     
     bool IsLeaf () const
     {
     	return !degree;
     }
     
     unsigned  int Degree() const
     {
     	return degree;
     }
     
     int Height() const;

     

    Object& Key () const;
    GeneralTree& Subtree (unsigned int) const;
    virtual void AttachSubtree (GeneralTree&);
    virtual GeneralTree& DetachSubtree (GeneralTree&);
    void Purge(void);
    void Put (std::ostream& s) const;
    
};

#endif /*GENERALTREE_H_*/
