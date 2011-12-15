//
//   This file contains the C++ code from Program 9.10 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm09_10.cpp
//

#include <GeneralTree.h>
#include <LinkedList.h>
#include <stdexcept>

using std::out_of_range;
using std::logic_error;

GeneralTree::GeneralTree (Object& _key) :
    key (&_key),
    degree (0),
    list ()
    {
    	count = 1;
    }

void GeneralTree::Purge ()
{
    ListElement<GeneralTree*> const* ptr;

    if (IsOwner ())
	delete key;
    for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
	delete ptr->Datum ();
    key = 0;
    list.Purge ();
}


int GeneralTree::Height() const     
     {
     	int height = 0;
     	if(!degree){
     		return  -1;
     	}
     	
     	 ListElement<GeneralTree*> const* ptr;
     	  for (ptr = list.Head (); ptr != 0; ptr = ptr->Next ())
     	  {
     	  	if (ptr->Datum ()->Height() > height){
     	  		height = ptr->Datum ()->Height();
     	  	}
     	  }
     	  
     	  return ++height;
     }


GeneralTree::~GeneralTree ()
    { Purge (); }

    
   
Object& GeneralTree::Key () const
    { return *key; }

GeneralTree& GeneralTree::Subtree (unsigned int i) const
{
    if (i >= degree)
	throw out_of_range ("invalid subtree index");

    unsigned int j = 0;
    ListElement<GeneralTree*> const* ptr =
	list.Head ();
    while (j < i && ptr != 0)
    {
	++j;
	ptr = ptr->Next ();
    }
    if (ptr == 0)
	throw logic_error ("should never happen");
    return *ptr->Datum ();
}

void GeneralTree::AttachSubtree (GeneralTree& t)
{
    list.Append (&t);
    ++degree;
}

GeneralTree& GeneralTree::DetachSubtree (GeneralTree& t)
{
    list.Extract (&t);
    --degree;
    return t;
}

void  GeneralTree::Put (std::ostream& s) const
{
	#ifdef DPRINT
	using namespace std;
	static int  i = 0;
	++i;
	cout<<"put :"<<i<<endl;
	#endif
	s<<*key;
}



