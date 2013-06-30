//
//   This file contains the C++ code from Program 10.8 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_08.cpp
//

#include <AVLTree.h>
#include <ToolKits.h>



#include <stdexcept>
#include <cmath>


AVLTree::AVLTree () :
    BST (),
    height (-1)
    {}

int AVLTree::Height () const
    { return height; }

void AVLTree::AdjustHeight ()
{
    if (IsEmpty ())
	height = -1;
    else
	height = Max (left->Height (), right->Height ()) + 1;
}

int AVLTree::BalanceFactor () const
{
    if (IsEmpty ())
	return 0;
    else
	return left->Height () - right->Height ();
}


void AVLTree::LLRotation ()
{
    if (IsEmpty ())
	throw std::domain_error ("invalid rotation");
    BinaryTree* const tmp = right;
    right = left;
    left = Right ().left;
    Right ().left = Right ().right;
    Right ().right = tmp;

    Object* const tmpObj = key;
    key = Right ().key;
    Right ().key = tmpObj;

    Right ().AdjustHeight ();
    AdjustHeight ();
}


void AVLTree::RRRotation ()
{
    if (IsEmpty ())
	throw std::domain_error ("invalid rotation");
    BinaryTree* const tmp = left;
    left = right;
    right = Left().right;
    Left().right = Left().left;
    Left().left = tmp;

    Object* const tmpObj = key;
    key = Left().key;
    Left().key = tmpObj;

    Left().AdjustHeight ();
    AdjustHeight ();
}



void AVLTree::LRRotation ()
{
    if (IsEmpty ())
	throw std::domain_error ("invalid rotation");
    Left ().RRRotation ();
    LLRotation ();
}


void AVLTree::RLRotation ()
{
    if (IsEmpty ())
	throw std::domain_error ("invalid rotation");
   Right ().LLRotation ();
    RRRotation ();
}



void AVLTree::Balance ()
{
    AdjustHeight ();
    if (abs (BalanceFactor ()) > 1)
    {
	if (BalanceFactor () > 0)
	{
	    if (Left ().BalanceFactor () > 0)
		LLRotation ();
	    else
		LRRotation ();
	}
	else
	{
	    if (Right ().BalanceFactor () < 0)
		RRRotation ();
	    else
		RLRotation ();
	}
    }
}

void AVLTree::AttachKey (Object& object)
{
    if (!IsEmpty ())
	throw std::domain_error ("invalid operation");
    key = &object;
    left = new AVLTree ();
    right = new AVLTree ();
    height = 0;
}

Object& AVLTree::DetachKey ()
{
    height = -1;
    return BST::DetachKey ();
}

    AVLTree& AVLTree:: Left () const
    {
    	return dynamic_cast<AVLTree &>(BST::Left());
    }
    
    AVLTree& AVLTree::Right () const
    {
    	return dynamic_cast<AVLTree &>(BST::Right());    	
    }

