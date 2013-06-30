//
//   This file contains the C++ code from Program 9.13 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_13.cpp
//

#include <NaryTree.h>
#include <stdexcept>

using std::domain_error;

NaryTree::NaryTree (unsigned int _degree) :
    key (0),
    degree (_degree),
    subtree (0)
    {}

NaryTree::NaryTree (unsigned int _degree, Object& _key):
    key (&_key),
    degree (_degree),
    subtree (_degree)
{
    for (unsigned int i = 0; i < degree; ++i)
	subtree [i] = new NaryTree (degree);
}


bool NaryTree::IsEmpty () const
    { return key == 0; }

Object& NaryTree::Key () const
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    return *key;
}

void NaryTree::AttachKey (Object& object)
{
    if (!IsEmpty ())
	throw domain_error ("invalid operation");
    key = &object;
    subtree.SetLength (degree);
    for (unsigned int i = 0; i < degree; ++i)
	subtree [i] = new NaryTree (degree);
}

Object& NaryTree::DetachKey ()
{
    if (!IsLeaf ())
	throw domain_error ("invalid operation");
    Object& result = *key;
    key = 0;
    for (unsigned int i = 0; i < degree; ++i)
	delete subtree [i];
    subtree.SetLength (0);
    return result;
}


NaryTree& NaryTree::Subtree (unsigned int i) const
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    return *subtree [i];
}

void NaryTree::AttachSubtree (unsigned int i, NaryTree& t)
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    if (!subtree [i]->IsEmpty ())
	throw domain_error ("non-empty subtree present");
    delete subtree [i];
    subtree [i] = &t;
}

NaryTree& NaryTree::DetachSubtree (unsigned int i)
{
    if (IsEmpty ())
	throw domain_error ("invalid operation");
    NaryTree& result = *subtree [i];
    subtree [i] = new NaryTree (degree);
    return result;
}


void NaryTree::Purge(void)
{
	if(IsEmpty()){
		return;
	}
	
	if(IsOwner() && !IsEmpty()){
		delete key;
	}
	
	for(unsigned int i = 0; i < degree && ! subtree[i]->IsEmpty(); i++){
		delete subtree[i];
	}
}
