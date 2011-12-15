//
//   This file contains the C++ code from Program 10.14 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_14.cpp
//

#include <MWayTree.h>
#include <PrePostVisitor.h>
#include <NullObject.h>

#include <stdexcept>


  MWayTree::MWayTree (unsigned int M) : m(M), 
  numberOfKeys (0), 	key(M)  ,subtree(M)
  {

  	
 	
  }
  

void MWayTree::DepthFirstTraversal (
    PrePostVisitor& visitor) const
{
    if (!IsEmpty ())
    {
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	    visitor.PreVisit (*key [i]);
	subtree [0]->DepthFirstTraversal (visitor);
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	{
	    visitor.Visit (*key [i]);
	    subtree [i]->DepthFirstTraversal (visitor);
	}
	for (unsigned int i = 1; i <= numberOfKeys; ++i)
	    visitor.PostVisit (*key [i]);
    }
    

}

/**************************************************************
Object& MWayTree::Find (Object const& object) const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    unsigned int i = numberOfKeys;
    while (i > 0)
    {
	int const diff = object.Compare (*key [i]);
	if (diff == 0)
	    return *key [i];
	if (diff > 0)
	    break;
	--i;
    }
    return subtree [i]->Find (object);
}
***************************************************************/


unsigned int MWayTree::FindIndex (Object const& object) const
{
    if (IsEmpty ())
	throw std::domain_error ("invalid operation");
    if (object < *key [1])
	return 0;
    unsigned int left = 1;
    unsigned int right = numberOfKeys;
    while (left < right)
    {
	int const middle = (left + right + 1) / 2;
	if (object >= *key [middle])
	    left = middle;
	else
	    right = middle - 1U;
    }

    return left;
}

Object& MWayTree::Find (Object const& object) const
{
    if (IsEmpty ())
	return NullObject::Instance ();
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
	return *key [index];
    else
	return subtree [index]->Find (object);
}

void MWayTree::Insert (Object& object)
{
    if (IsEmpty ())
    {
	subtree [0] = new MWayTree (m);
	key [1] = &object;
	subtree [1] = new MWayTree (m);
	numberOfKeys = 1;
    }
    else
    {
	unsigned int const index = FindIndex (object);
	if (index != 0 && object == *key [index])
	    throw std::invalid_argument ("duplicate key");
	if (numberOfKeys < m - 1U)
	{
	    for(unsigned int i = numberOfKeys; i > index; --i)
	    {
		key [i + 1] = key [i];
		subtree [i + 1] = subtree [i];
	    }
	    key [index + 1] = &object;
	    subtree [index + 1] = new MWayTree (m);
	    ++numberOfKeys;
	}
	else
	    subtree [index]->Insert (object);
    }
}


void MWayTree::Withdraw (Object& object)
{
    if (IsEmpty ())
	throw std::invalid_argument ("object not found");
    unsigned int const index = FindIndex (object);
    if (index != 0 && object == *key [index])
    {
	if (!subtree [index - 1U]->IsEmpty ())
	{
	    Object& max = subtree [index - 1U]->FindMax ();
	    key [index] = &max;
	    subtree [index - 1U]->Withdraw (max);
	}
	else if (!subtree [index]->IsEmpty ())
	{
	    Object& min = subtree [index]->FindMin ();
	    key [index] = &min;
	    subtree [index]->Withdraw (min);
	}
	else
	{
	    --numberOfKeys;
	    delete subtree [index];
	    for(unsigned int i = index; i <= numberOfKeys; ++i)
	    {
		key [i] = key [i + 1];
		subtree [i] = subtree [i + 1];
	    }
	    if (numberOfKeys == 0)
		delete subtree [0];
	}
    }
    else
	subtree [index]->Withdraw (object);
}


unsigned int MWayTree::Degree() const
	{
		unsigned int d = 0;
		for(unsigned int i = 0 ; i < m; ++i){
			if( !subtree[i] ){
				continue;
			}
			
			if( subtree[i] -> IsEmpty()){
				continue;
			}
			
			++d;
		}
		return d;
	}
	
unsigned int MWayTree::Count() const 
{
	return numberOfKeys;
}
 
	
	
Object& MWayTree::FindMin() const
	{
		if(IsEmpty()){
			throw std::domain_error ("invalid operation");
		}
		
		if(IsLeaf()){
			return Key(1) ;
		}else{
			unsigned int i = 0 ;
			for(; i < m  ; i ++){
				
				
				if(subtree[i] ){
					if( !subtree[i]->IsEmpty()   ){
						break;
					}	
				}
			
			  if(key[i +1]  ){
			  	break;
			  }
			  
			}
			
			if(i == m){
				throw std::logic_error ("no subtree found while there must be one subtree exist at least");
			}
			
			if(subtree[i]->IsEmpty())
			{
				return *key[i +1];
			}else{
				return subtree[i] -> FindMin();
			}
		}
	}
	
	
	Object&  MWayTree::FindMax() const
	{
			if(IsEmpty()){
			throw std::domain_error ("invalid operation");
		}
		
		if(IsLeaf()   || Subtree(Count() ). IsEmpty()  ){
			return Key(Count()) ;
		}else{
			return Subtree(Count() ).FindMax();
		}
	}

MWayTree  &MWayTree::Subtree(unsigned int i) const
{
		if(! subtree[i] ){
			throw std::domain_error ("invalid operation");
		}
		
		return *subtree[i];
}


	
void MWayTree::Purge(void)
{ 
	
	if(IsEmpty()){// do nothing for a empty tree
		return ;
	}
	
	
	if(IsOwner()){
		for(unsigned i = 1; i <= numberOfKeys; i++){
			delete key[i];
		}
	}
	
		
		for(unsigned i = 0 ; i <= numberOfKeys; i++){
			//if(subtree[i]){
				delete subtree[i ];
				subtree[i ] = 0;
				
			//}
		}		
		numberOfKeys = 0;	
	
}

	



