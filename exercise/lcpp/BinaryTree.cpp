//
//   This file contains the C++ code from Program 9.17 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_17.cpp
//

#include <BinaryTree.h>



BinaryTree::BinaryTree () :
    key (0),
    left (0),
    right (0)
    {}

BinaryTree::BinaryTree (Object& _key) :
    key (&_key),
    left (new BinaryTree ()),
    right (new BinaryTree ())
    {}

    
    void BinaryTree::Purge ()
{
    if (!IsEmpty ())
    {
	if (IsOwner ())
	    delete key;
	delete left;
	delete right;
	key = 0;
	left = 0;
	right = 0;
    }
}

BinaryTree::~BinaryTree ()
    { Purge (); }
    
 
 void BinaryTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
	
    if (visitor.IsDone ())
	return;
    if (!IsEmpty ())
    {
    	#ifdef DPRINT
    	std::cerr<< "DepthFirstTraversal @  this= "<<this<<" key="<< *key<<" left=" <<left << " right ="<<right<<std::endl;
    	#endif
	visitor.PreVisit (*key);
	if(left){
		left->DepthFirstTraversal (visitor);
	}
	
	
	visitor.Visit (*key);
	
	if(right){
		right->DepthFirstTraversal (visitor);
	}
	
	
	visitor.PostVisit (*key);
    }
}
 
 
 int BinaryTree::CompareTo (Object const& object) const
{
    BinaryTree const& arg = 
	dynamic_cast<BinaryTree const&> (object);
    if (IsEmpty ())
	return arg.IsEmpty () ? 0 : -1;
    else if (arg.IsEmpty ())
	return 1;
    else
    {
	int result = Key ().Compare (arg.Key ());
	if (result == 0)
	    result = Left ().CompareTo (arg.Left ());
	if (result == 0)
	    result = Right ().CompareTo (arg.Right ());
	return result;
    }
}   


    BinaryTree& BinaryTree::Subtree(unsigned int i) const
    {
    	unsigned int  degree = Degree();
    	if( i >= degree)
    	{
    		throw std::domain_error("Invalid position");
    	}
    	
    	if(IsEmpty()){
    		throw std::domain_error("Empty tree");
    	}
    	
    	
    	if(  ( i  == 0 ) ){
    		if(left){
    			return *left;
    		}else if(degree ==1 && right) {
    			return *right;
    		}else{
    			throw std::logic_error("something error");
    			}
    	
    	}

    		if(!right){
    			throw std::logic_error("something error");
    		}
    		
    		return *right;

    	
    	
  }

int BinaryTree::Height () const
{
	int height = -1;
	if(IsEmpty()){
		return height;
	}
	
	if(left){
		if( height < left->Height()){
			height =  left->Height();
			}
		}
		
		if(right){
		
		if(height < right->Height()){
			height = right->Height();
			}
		}
	
	return ++height;
}


