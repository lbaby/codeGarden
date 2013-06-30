//
//   This file contains the C++ code from Program 9.16 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_16.cpp
//

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <Tree.h>
#include <Object.h>
#include <stdexcept>



class BinaryTree : public virtual Tree
{
protected:
    Object* key;
    BinaryTree* left;
    BinaryTree* right;
    int CompareTo(const Object & ) const;
public:
    BinaryTree ();
    BinaryTree (Object&);
    ~BinaryTree ();
    
    bool IsEmpty() const
    {
    	return  !key; 
    }
    
    
    bool IsLeaf() const
    {
    	return !IsEmpty() && 
    	(left ?   left->IsEmpty() :true) && (right ? right->IsEmpty():true) ;
    }
    
    int Height () const;
    
    
    unsigned int Degree(void) const
    {
    	unsigned int degree = 0;
    	if(left){
    		degree ++;
    	}
    	if(right){
    		degree ++;
    	}
    	
    	return degree;
    		
    }
    
    BinaryTree& Subtree(unsigned int i) const;
    	
    	
    
    

    Object& Key () const
    {
       	if(!key){
    		throw std::domain_error("the key is  NULL");
    	}
    	return *key;
    }
    
    
    virtual void AttachKey (Object& o)
    {
    	if(key){
    		throw std::domain_error("the key is not NULL");
    	}
    	
    	key = &o;
    }
    
    
    	
    virtual Object& DetachKey ()
    {
    	if(!key){
    	throw std::domain_error("the key is NULL");
    	}
    
    	return *key;
    }

    virtual BinaryTree& Left () const
    {
    	if(!left){
    		throw std::domain_error("Left is NULL");
    	}
    	
    	return *left;
    }
    
    
    virtual BinaryTree& Right () const
        {
    	if(!right){
    		throw std::domain_error("Right is NULL");
    	}
    	
    	return *right;
    }
    
    virtual void AttachLeft (BinaryTree& bt)
    {
    	    	if(left){
    		delete left;
    		}
    		left = &bt;
    }
    
    virtual void AttachRight (BinaryTree& bt)
        {
    	    	if(right){
    		delete right;
    		}
    		right = &bt;
    }
    
    virtual BinaryTree& DetachLeft ()    
    {
    	    	if(!left){
    		throw std::domain_error("Left is  NULL");
    		}
    		return *left;
    }
    
    virtual BinaryTree& DetachRight ()
    
        {
    	    	if(!right){
    		throw std::domain_error("right is  NULL");
    		}
    		
    		return *right;
    }
    
    void DepthFirstTraversal(PrePostVisitor&) const;
    
   void  Purge(void );
};

#endif /*BINARYTREE_H_*/
