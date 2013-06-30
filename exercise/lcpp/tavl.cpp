#include <AVLTree.h>
#include <iostream>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>


int main(void)
{
	using namespace std;
	AVLTree avl;
	
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);
	Int *ip4 = new Int(4);
	Int *ip5 = new Int(5);
	Int *ip6 = new Int(6);
	Int *ip7 = new Int(7);
	
	avl.Insert(*ip4);
	avl.Insert(*ip1);
	avl.Insert(*ip2);
	avl.Insert(*ip3);
	avl.Insert(*ip5);
	avl.Insert(*ip6);
	avl.Insert(*ip7);
	
	
	
	
	
		PuttingVisitor pv(cout);
	PreOrder po (pv);
	cout <<" *ip4 is member of  bst?:"<< avl.IsMember(*ip4)<< endl;
	cout <<" *ip1 found ?: "<< avl.Find(*ip1)<<endl;
	cout <<" max in bst: "<< avl.FindMax() <<endl;
	cout <<" min in avl : " << avl.FindMin() <<endl;
		avl.DepthFirstTraversal(po);
		cout << endl;
	cout <<" after withdraw *ip5:"<< endl;
	avl.Withdraw(*ip6);
		avl.DepthFirstTraversal(po);
	

	
	


	
}
