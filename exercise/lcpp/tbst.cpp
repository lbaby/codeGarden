#include <BST.h>
#include <iostream>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>


int main(void)
{
	using namespace std;
	BST bst;
	
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);
	Int *ip4 = new Int(4);
	Int *ip5 = new Int(5);
	Int *ip6 = new Int(6);
	Int *ip7 = new Int(7);
	
	bst.Insert(*ip4);
	bst.Insert(*ip1);
	bst.Insert(*ip2);
	bst.Insert(*ip3);
	bst.Insert(*ip5);
	bst.Insert(*ip6);
	bst.Insert(*ip7);
	
		BinaryTree &t = dynamic_cast< BinaryTree &> ( bst);
	
	
	
		PuttingVisitor pv(cout);
	PreOrder po (pv);
	cout <<" *ip4 is member of  bst?:"<< bst.IsMember(*ip4)<< endl;
	cout <<" *ip1 found ?: "<< bst.Find(*ip1)<<endl;
	cout <<" max in bst: "<< bst.FindMax() <<endl;
	cout <<" min in bst : " << bst.FindMin() <<endl;
		t.DepthFirstTraversal(po);
		cout << endl;
	cout <<" after withdraw *ip5:"<< endl;
	bst.Withdraw(*ip6);
		t.DepthFirstTraversal(po);
	

	
	


	
}
