//
//   This file contains the C++ code from Program 10.20 of
//   "Data Structures and Algorithms
//    with Object-Oriented Design Patterns in C++"
//   by Bruno R. Preiss.
//
//   Copyright (c) 1998 by Bruno R. Preiss, P.Eng.  All rights reserved.
//
//   http://www.pads.uwaterloo.ca/Bruno.Preiss/books/opus4/programs/pgm10_20.cpp
//

#include <BTree.h>
#include <NullObject.h>

#include <stdexcept>



BTree:: BTree (unsigned int M):MWayTree(M), parent(0)
{}


BTree::BTree (unsigned int M, BTree& b):MWayTree(M), parent(&b)
{}





void BTree::Insert (Object& object)
{

#ifdef DPRINT
        std::cerr<<" insert object = "<< object<<"@ numberOfKeys =" << numberOfKeys
        <<std::endl;
        for(unsigned int i = 1 ; i <= numberOfKeys ; i++) {
                std::cerr<<"key["<<i<<"]  "<<*key[i]<<std::endl;
        }

#endif
        if (IsEmpty ()) {
#ifdef DPRINT
                std::cerr<<" EMPTY  ROOT insert object = "<< object
                <<std::endl;

#endif

                if (parent == 0) {
                        AttachSubtree (0, *new BTree (m, *this));
                        AttachKey (1, object);
                        AttachSubtree (1, *new BTree (m, *this));
                        numberOfKeys = 1;
                } else {
                        parent->InsertPair (object, *new BTree (m, *parent));

                }

        } else {
                unsigned int const index = FindIndex (object);

                if (index != 0 && object == *key [index])
                        throw  std::invalid_argument ("duplicate key");
                subtree [index]->Insert (object);
        }
}


void BTree::InsertPair (Object& object, BTree& child)
{


        unsigned int const index = FindIndex (object);
        BTree& extraTree = InsertSubtree (index + 1, child);
        Object& extraKey = InsertKey (index + 1, object);
#ifdef DPRINT

        std::cerr<<" insertPair object = " << object <<"numberOfKeys = "
        << numberOfKeys<<" index = "<< index<<std::endl;
#endif

        ++ numberOfKeys;
        if (numberOfKeys == m) {
#ifdef DPRINT
                std::cerr<<" overflow @ object = "<< object<<" numberOfKeys ="<< numberOfKeys<<std::endl;
#endif

                if (parent == 0) {
                        BTree& left = *new BTree (m, *this);
                        BTree& right = *new BTree (m, *this);
                        left.AttachLeftHalfOf (*this);
                        right.AttachRightHalfOf (*this, extraKey, extraTree);
                        AttachSubtree (0, left);
                        AttachKey (1, *key [(m + 1)/2]);
                        AttachSubtree (1, right);
                        numberOfKeys = 1;
                } else {

                        numberOfKeys = (m+1)/2 -1;
                        BTree& right = *new BTree (m, *parent);
                        right.AttachRightHalfOf (*this, extraKey, extraTree);
                        // this is addon for debug


                        Object &omid = *key [(m + 1)/2];

                        //

                        parent->InsertPair (omid, right);
                }
        }
}


void BTree::AttachSubtree (unsigned int i, MWayTree& mt)
{
        /* no necessary to check the bound
        if(subtree[i]){
        	if(!subtree[i]->IsEmpty()){
        		throw  std::domain_error ("Subtree  already exist");
        	}else{
        		delete subtree[i];
        	}
        }
        */

        subtree[i] = &mt;
        //NOTE: once  a  subtree  is attached , his parent is curent node
        //don't omit this , or you will encounter some strange error.
        BTree &bt = dynamic_cast<BTree &>(mt);
        bt.parent = this;
}

void BTree::AttachKey (unsigned int i, Object& o)
{

        key[i] = &o;

}


void BTree::AttachLeftHalfOf (BTree const& bt)
{

        unsigned int mid = (m  +1 ) / 2    ;
        for(unsigned int i = 1 ; i <  mid  ; i ++) {
                AttachKey(i , * (bt.key[i] ) );
        }

        for(unsigned int i = 0 ; i < mid ; i ++) {

                AttachSubtree( i , *bt.subtree[i]);
        }

        numberOfKeys = mid  -1   ;

#ifdef DPRINT

        std::cerr<< " attach left  numberOfKeys "<< numberOfKeys << std::endl;
        for(unsigned int i = 1 ; i <= numberOfKeys ; i++) {
                std::cerr<<"key["<<i<<"]  "<<*key[i]<<std::endl;
        }
#endif
}



void BTree::AttachRightHalfOf (BTree const& sbt , Object& maxo, BTree& maxbt)
{

        unsigned int mid = (m +1 )  / 2      ;
        for(unsigned int i  =   mid + 1   ; i < m ; i ++) {
#ifdef DPRINT
                std::cerr<< " attachRightHalfOf  key[ "<< i  <<" ] = " << *sbt.key[i] << std::endl;

#endif

                AttachKey(i - mid   , * (sbt.key[i] ) );

#ifdef DPRINT

                std::cerr<< " after attachRightHalfOf  key[ "<<  ( i - mid   + 1) <<" ] = " <<  *key[i - mid   ]
                << " I  mid  "<< i  << " mid"<< mid << std::endl;

#endif

        }

        for(unsigned int i =   mid   ; i < m    ; i ++) {
                AttachSubtree( i - mid  , *sbt.subtree[i]);
        }




        numberOfKeys =   m -  mid -1    ;

        AttachSubtree(numberOfKeys + 1 , maxbt);

        AttachKey(numberOfKeys  +1 ,    maxo);


        numberOfKeys ++;


#ifdef DPRINT

        std::cerr<< " attach right  numberOfKeys "<< numberOfKeys << std::endl;
        for(unsigned int i = 1 ; i <= numberOfKeys ; i++) {
                std::cerr<<"key["<<i<<"]  "<<key[i] <<" ";
                if(key[i])
                        std::cerr<<*key[i]  ;
                std::cerr<<std::endl;
        }
        std::cerr<< " maxo " << maxo<<std::endl;
#endif

}


Object&  BTree::InsertKey (unsigned int i, Object& o)
{
        if(i > numberOfKeys + 1) {
                throw  std::invalid_argument ("Invalid position");
        }



        Object *oret  = 0;
        //insert to Tail
        if( i == numberOfKeys +1) {
                oret = &o;
                // Tail : if is full , just return the object
                //else insert into the tail
                if( i   != m) {
                        key[i] = &o;
                }
        } else { //  insert point is not tail
                //the last one of key's pointer is return value
                oret = key[numberOfKeys] ;

                unsigned int j = numberOfKeys;


                while ( j > i) {
                        key[j ]  = key [ j-1];
                        --j;
                }

                if(numberOfKeys + 1 < m) {
                        key[ numberOfKeys + 1] = oret;
                }

                key [i] = &o;
        }

#ifdef DPRINT

        std::cerr<< "insert Key : " << o  << "  index  "<< i  << " return  = " << *oret<< std::endl;
        std::cerr<<" after insertKey:"<< std::endl;

        for(unsigned int i = 1 ; i <= ( (numberOfKeys +1 ) < m   ?   (numberOfKeys +1 ) :  numberOfKeys  ) ; i++) {
                std::cerr<<"key["<<i<<"]  "<<key[i] <<" ";
                if(key[i])
                        std::cerr<<*key[i]  ;
                std::cerr<<std::endl;
        }

#endif

        return  *oret;
}



BTree& BTree:: InsertSubtree (unsigned int i, BTree& bt)
{
        if( i > numberOfKeys +1 ) {
                throw  std::invalid_argument ("Invalid position");
        }




        BTree *btret = 0;
        // insert into  tail
        if( i  ==   numberOfKeys + 1 ) {
                btret  = &bt;
                // if overflow , do nothing
                if(  i   != ( m ) ) {
                        subtree [i ] = &bt;
                        bt.parent = this;
                }
        } else { // the insert point is not tail;
                btret =dynamic_cast<BTree *>
                       (subtree[numberOfKeys]   );
                //not overflow
                unsigned int j =  numberOfKeys;

                for(;  j >  i ; j--) {
                        subtree[j] = subtree[j-1];
                }

                if(numberOfKeys + 1 < m) {
                        subtree[numberOfKeys + 1 ] = btret;
                }


                subtree[i] = &bt;
                bt.parent = this;
        }



        return *btret;

}



void BTree::Withdraw (Object& object)
{
        if (IsEmpty ())
                throw std::invalid_argument ("object not found");

       
        unsigned int const index = FindIndex (object);
        // Move the object to a proper position, so that it's easy to  erase
        if (index != 0 && object == *key [index]) {
                //To move left(smaller) , we should exchange it with left's max
                //on the opposite  , we do the same as left
                if (!subtree [index - 1U]->IsEmpty ()) {
                        Object& max = subtree [index - 1U]->FindMax ();
                        if(IsOwner()) {
                                delete key[index];
                        }
                        key [index] = &max;
                        subtree [index - 1U]->Withdraw (max);
                } else if (!subtree [index]->IsEmpty ()) {
                        Object& min = subtree [index]->FindMin ();
                        if(IsOwner()) {
                                delete key[index];
                        }
                        key [index] = &min;
                        subtree [index]->Withdraw (min);
                } else {
#ifdef DPRINT
                        std::cerr<<"Withdraw:  " << object <<"& key[index] "<< *key[index]<<std::endl;
#endif
                        //not
                        delete subtree [index];
                        subtree[index] = 0;

                        key[index] = 0;

                        for(unsigned int i = index; i < numberOfKeys; ++i) {
                                key [i] = key [i + 1];
                                subtree[i] = subtree[i + 1];

                        }
                        


                        --numberOfKeys;
                       #ifdef DPRINT
                        std::cerr<<"Withdraw:  " << object <<"after : numberOfKeys="<< numberOfKeys <<std::endl;
                        #endif 
                        /*
                        if (numberOfKeys == 0) { // a empty tree
                                delete subtree [0];
                                subtree[0] = 0;

                        }*/
                        

                  #ifdef DPRINT
                        std::cerr<<"Withdraw:  " << object <<"after : numberOfKeys="<< numberOfKeys <<std::endl;
                   #endif 


          
                   #ifdef DPRINT
                        std::cerr<<"Withdraw:  after delete " << "parent= "<< parent<<std::endl;
                        #endif
                        
                         if(numberOfKeys < (m+1)/2 -1 ) {// Out of balance, request balance for parent
                                //Note:  if it is root , do nothing.
                                if(parent) {
                                        parent->Balance(  this  );
                                }
                        }
                       
                       
          


                }//else


        } else {
                subtree [index]->Withdraw (object);
        }
}



//The argument is  used to find out  what subtree shoud be balanced
//  Only because we have got more than two subtrees ,  and the subtree themself do  not know
//what index they is in the parent.
void BTree::Balance(const BTree * const btidx )
{


        // no need to balance for a root btree
       if(!parent && !numberOfKeys){
       	return;
       }


        
        #ifdef DPRINT
        std::cerr<<"balance @"<< btidx  << "  & this = "<< this<< std::endl;
        #endif
         unsigned int index = 0;
         while(index <=  numberOfKeys){
         	if(subtree[index] == btidx){
         		break;
         	}
         	index++;
         }

        if( index > numberOfKeys ) {
                throw std::invalid_argument("Balnace: bad index");
        }

        //LL Rotation
        if( index != 0) {
                BTree *left = dynamic_cast<BTree *>(subtree[index -1 ]);
                BTree *right =  dynamic_cast<BTree *>(subtree[index  ]);

                if(  (right->Count() ==  (m+1)/2 -2)
                                &&(left->Count()  >= (m + 1)/2) ) {
                        //move current key an left.max to right
                        right->InsertSubtree(0U, dynamic_cast<BTree &>(*left->subtree[left->numberOfKeys] ));
                        right->InsertKey(1U , *key[index ]);
                        ++right->numberOfKeys;

                        key[index ] = left->key[left->numberOfKeys];
                        left->key[left->numberOfKeys] = 0;
                        left->subtree[left->numberOfKeys] = 0;
                        -- left -> numberOfKeys;
                       
                       return ;
                        //merge
                } else if( (right->Count() ==  (m+1)/2 -2)
                                &&(left->Count()   == (m + 1)/2 -1 ) ) {
         
                        left->InsertSubtree( left->numberOfKeys + 1  , dynamic_cast<BTree &>( *right->subtree[0])  );
                        left->key[left->numberOfKeys + 1] = key[index];
                        left -> numberOfKeys ++;
                        right->subtree[0] = 0;

                        
                        for(unsigned int i = 1; i <= right->numberOfKeys ; i++) {
                                left->InsertSubtree(left->numberOfKeys + 1   , dynamic_cast<BTree &>( *right->subtree[i] ));
                                right->subtree[i] = 0;
                                left->key[left->numberOfKeys + 1  ] = right->key[i];
                                right->key[i] = 0;
                                
                                ++left->numberOfKeys;

                        }
                        

                         
                        right->numberOfKeys = 0;

                        for(unsigned int i = index   ; i < numberOfKeys ; i++) {
                                key[i] = key[i+1];
                                subtree[i] = subtree[i+1];
                        }
                        key [ numberOfKeys] = 0;
                        subtree[numberOfKeys] = 0;

                        numberOfKeys --;

                        if(parent) {
                                parent->Balance(this);
                        }
                        
                        //Root now empty after balance , but children not empty now 
                        if(!parent && !numberOfKeys && !subtree[0] -> IsEmpty()){
                        	BTree  *lchild  = dynamic_cast<BTree * >(subtree[0]);
                        	for(unsigned int i = 0  ; i <= lchild->numberOfKeys ; i ++){
                        		InsertSubtree(i, dynamic_cast<BTree & >( * lchild -> subtree[i] ) );
                        		if(i<  lchild->numberOfKeys ){
                        			key[i + 1] = lchild -> key[ i + 1];
                        			numberOfKeys ++;
                        		}
                        		
                        	}
                        	

                    
                        	
                        	
                        }
                        return ;

                }
                

        } 
        
          if (index != numberOfKeys) {
                BTree *left = dynamic_cast<BTree *>(subtree[index ]);
                BTree *right =  dynamic_cast<BTree *>(subtree[index  +  1U]);
                if( (left->Count() ==  (m+1)/2 -2)
                                &&(right->Count() >= (m + 1)/2) ) {// RR Rotation


                        left->InsertSubtree(left->numberOfKeys +1U, dynamic_cast<BTree &>(*right->subtree[0] ));
                        left->InsertKey(left->numberOfKeys +1U , *key[index + 1]);
                        ++left->numberOfKeys;

                        key[index +1] = right->key[1];
                        for(unsigned int i = 0;
                                        i <  right-> numberOfKeys ;
                                        ++i) {
                                right->subtree[i]
                                = right->subtree[i +1];
                        }

                        for(unsigned int i = 1;
                                        i < right->numberOfKeys ;
                                        ++i) {
                                right->key[i ]
                                = right->key [i +1];
                        }
                        right->subtree[right->numberOfKeys] = 0;
                        right->key[right->numberOfKeys ] = 0;
                        --right -> numberOfKeys;
                        return ;
                        //////////////////////////////////////////////////////////////////
                        //merge
                } else if((left->Count() ==  (m+1)/2 -2)
                                &&(right->Count()   == (m + 1)/2 -1 )) {
                        left->InsertSubtree(left->numberOfKeys + 1 , dynamic_cast<BTree &>(*right->subtree[0] ) );
                        left->key[left->numberOfKeys + 1] = key[index +1];
                        left -> numberOfKeys ++;
                        
                        for(unsigned int i = 1; i <= right->numberOfKeys ; i++) {
                                left->InsertSubtree(left->numberOfKeys + 1,  dynamic_cast<BTree &>(*right->subtree[i] ));
                                right->subtree[i] = 0;
                                left->key[left->numberOfKeys + 1  ] = right->key[i];
                                right->key[i] = 0;
                                left->numberOfKeys ++;

                        }
                        
                       
                        right->numberOfKeys = 0;

                        for(unsigned int i = index +1 ; i < numberOfKeys ; i++) {
                                key[i] = key[i+1];
                                subtree[i] = subtree[i+1];
                        }
                        
                        key[numberOfKeys ] = 0;
                        subtree[numberOfKeys] = 0;
                        numberOfKeys --;

                        if(parent) {
                                parent->Balance(this);
                        }
                        
                        //Root now empty after balance , but children not empty now 
                        if(!parent && !numberOfKeys && !subtree[0] -> IsEmpty()){
                        	BTree  *lchild  = dynamic_cast<BTree * >(subtree[0]);
                        	for(unsigned int i = 0  ; i <= lchild->numberOfKeys ; i ++){
                        		InsertSubtree(i, dynamic_cast<BTree & >( * lchild -> subtree[i] ) );
                        		if(i<  lchild->numberOfKeys ){
                        			key[i + 1] = lchild -> key[ i + 1];
                        			numberOfKeys ++;
                        		}
                        		
                        	}
                        }
                        	
                        return ;

                }
        }




}







#ifdef DPRINT
void BTree::printTree(void)
{
        if(! IsEmpty()) {
                std::cerr<<"this = "<<this <<":" <<std::endl;
                for(unsigned int i = 1; i <= numberOfKeys; i ++) {
                        std::cerr<<"key [ "<< i<<" ]  = "<<*key[i] <<std::endl;
                }

                for(unsigned int i = 0; i <= numberOfKeys; i ++) {
                        std::cerr<<"subtree  [ "<< i<<" ]  = "<<subtree [i] <<std::endl;
                }

                for(unsigned int i = 0; i <= numberOfKeys; i ++) {
                        BTree *bt = dynamic_cast<BTree *>(subtree [i]);
                        bt  -> printTree();
                }

        }else {
        	std::cerr<<"this = "<< this <<std::endl<< "empty"<<std::endl;
        }

}
#endif

