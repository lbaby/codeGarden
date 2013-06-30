#include <BTree.h>
#include <iostream>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>
#include <vector>



int main(void)
{
	using namespace std;
	BTree btree(5);
	
	vector <Int *> vp ;
	
	for(int i = 0; i < 25; i ++){
		Int * ip = new Int(i);
		vp.push_back(ip);
		btree.Insert(*ip);
	}
	

	
	PuttingVisitor pv(cout);
	PreOrder po (pv);

	btree.DepthFirstTraversal(po);
	cout << endl;
	
	
			for(int i = 0; i < 25; i ++){
			btree.Withdraw(* vp[i]);
			#ifdef DPRINT
			btree.printTree();
			#endif
	}
	
	cout << "main: end of test btree"<< endl;


	
}
