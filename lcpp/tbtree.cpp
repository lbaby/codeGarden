#include <BTree.h>
#include <iostream>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>


int main(void)
{
	using namespace std;
	{
	BTree btree(4);
	
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);
	Int *ip4 = new Int(4);
	Int *ip5 = new Int(5);
	Int *ip6 = new Int(6);
	Int *ip7 = new Int(7);
	Int *ip8 = new Int(8);
	Int *ip9 = new Int(9);
	Int *ip10 = new Int(10);
	
	
	Int *ip11 = new Int(11);
	Int *ip12 = new Int(12);
	Int *ip13 = new Int(13);
	Int *ip14 = new Int(14);
	Int *ip15 = new Int(15);
	Int *ip16 = new Int(16);
	Int *ip17 = new Int(17);
	
	Int *ipa17 = new Int(17);
	
	btree.Insert(*ip4);
	btree.Insert(*ip17);

	
	btree.Insert(*ip1);
	btree.Insert(*ip2);
	

	
	btree.Insert(*ip3);

	btree.Insert(*ip5);
	
	btree.Insert(*ip6);

	btree.Insert(*ip7);
	

	
	btree.Insert(*ip8);
	btree.Insert(*ip9);
	btree.Insert(*ip10);
	
	btree.Insert(*ip14);
	btree.Insert(*ip11);
	btree.Insert(*ip12);
	btree.Insert(*ip13);
	btree.Insert(*ip15);
	btree.Insert(*ip16);
	
	//btree.Withdraw(*ip17);
	try {
		btree.Insert(*ipa17);
	}
	catch( exception  &e){
		cout <<  "Insert fail : reason:"<<e.what() <<endl;
	}
		
	
	
	
	
	
	
		PuttingVisitor pv(cout);
	PreOrder po (pv);
	
	cout << "\n\n"<<endl;
	cout <<" *ip4 is member of  bst?:"<< btree.IsMember(*ip4)<< endl;
	cout <<" *ip1 found ?: "<< btree.Find(*ip1)<<endl;
	cout<<" *ip17 found?:"<<btree.Find(*ipa17)<<endl;
	cout <<" max in bst: "<< btree.FindMax() <<endl;
	cout <<" min in btree : " << btree.FindMin() <<endl;


	#ifdef DPRINT
	btree.printTree();
	#endif
	
	btree.DepthFirstTraversal(po);
	cout << endl;
	cerr<<"main:withdraw "<<*ip4<<endl;
	btree.Withdraw(*ip4);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main:withdraw "<<*ip1<<endl;
	btree.Withdraw(*ip1);
	cerr<<"main:withdraw "<<*ip2<<endl;
	btree.Withdraw(*ip2);
	cerr<<"main:withdraw "<<*ip3<<endl;

	
	btree.Withdraw(*ip3);		
	
	#ifdef DPRINT
	btree.printTree();
	#endif
	
	cerr<<"main:withdraw "<<*ip5<<endl;
	btree.Withdraw(*ip5);
		#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main:withdraw "<<*ip6<<endl;
	btree.Withdraw(*ip6);
	#ifdef DPRINT
	btree.printTree();
	#endif
cerr<<"main:withdraw "<<*ip7<<endl;
	btree.Withdraw(*ip7);
	
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip8<<endl;
	btree.Withdraw(*ip8);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip9<<endl;
	btree.Withdraw(*ip9);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip10<<endl;
	btree.Withdraw(*ip10);
	
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip14<<endl;
	btree.Withdraw(*ip14);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip11<<endl;
	btree.Withdraw(*ip11);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip12<<endl;
	btree.Withdraw(*ip12);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip13<<endl;
	btree.Withdraw(*ip13);
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip15<<endl;
	btree.Withdraw(*ip15);
	
	#ifdef DPRINT
	btree.printTree();
	#endif
	cerr<<"main: withdraw  "<<*ip16<<endl;
	btree.Withdraw(*ip16);
		
	btree.DepthFirstTraversal(po);
	cout << endl;
	
	}
	cout << "main: end of test btree"<< endl;


	
}
