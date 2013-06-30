#ifndef LEFTISTHEAP_H_
#define LEFTISTHEAP_H_

//
//   This file contains the C++ code from Program 11.7 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm11_07.cpp
//

#include <BinaryTree.h>
#include <PriorityQueue.h>
#include <Object.h>

class LeftistHeap :
    public BinaryTree, public MergeablePriorityQueue
{
    unsigned int nullPathLength;

    void SwapContents (LeftistHeap& arg)
    {
    	BinaryTree *ltmp =  left;
    	left  = arg.left;
    	
    	arg.left = ltmp;
    	
    	ltmp = right;
    	
    	right = arg.right;
    	arg.right = ltmp;
    	
    	Object * k = key;
    	key = arg.key;
    	arg.key = k;
    	
    	unsigned int npl = nullPathLength ;
    	nullPathLength = arg.nullPathLength;
    	arg.nullPathLength = npl;
    }
public:
    LeftistHeap ():BinaryTree::BinaryTree(),nullPathLength(0)
    {}
    LeftistHeap (Object& o):BinaryTree::BinaryTree(o),nullPathLength(1)
    {
    	left = new LeftistHeap ();
    	right = new LeftistHeap ();
    }
    
    ~LeftistHeap();
 

    LeftistHeap& Left () const
    {
    	return dynamic_cast<LeftistHeap &>(*left);
    }
    
    LeftistHeap& Right () const
    {
    	return dynamic_cast<LeftistHeap &>( *right);
    }
    
    void Merge (MergeablePriorityQueue&);
    
    bool IsEmpty(void) const 
    {
    	return !key;
    }
    
    Object& FindMin () const;
    Object& DequeueMin ();
    void Enqueue (Object& object);
    
};

#endif /*LEFTISTHEAP_H_*/
