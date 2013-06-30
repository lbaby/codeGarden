#include <MWayTree.h>
#include <iostream>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>


int main(void)
{
	using namespace std;
	MWayTree mwt(3);
	
	
	
	PuttingVisitor pv(cout);
	PreOrder po (pv);
	
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);

	Int *ip4 = new Int(4);
	Int *ip5 = new Int(5);
	Int *ip6 = new Int(6);
	Int *ip7 = new Int(7);	
	Int *ip8 = new Int(8);
	Int *ip9 = new Int(9);

		
	mwt.Insert(*ip4);
	mwt.Insert(*ip1);
	mwt.Insert(*ip2);
	mwt.Insert(*ip3);
	
		mwt.DepthFirstTraversal(po);
	cout << endl;
	mwt.Insert(*ip5);
	mwt.Insert(*ip6);
	mwt.Insert(*ip7);
	mwt.Insert(*ip8);
	mwt.Insert(*ip9);
	

	
	cout <<" *ip4 is member of  mwt?:"<< mwt.IsMember(*ip4)<< endl;
	cout <<" *ip1 found ?: "<< mwt.Find(*ip1)<<endl;
	cout <<" max in mwt: "<< mwt.FindMax() <<endl;
	cout <<" min in mwt : " << mwt.FindMin() <<endl;
		mwt.DepthFirstTraversal(po);
		cout << endl;
	cout <<" after withdraw *ip5:"<< endl;
	mwt.Withdraw(*ip6);
		mwt.DepthFirstTraversal(po);
	
	cout << endl;

	
	


	
}
