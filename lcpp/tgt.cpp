#include <GeneralTree.h>
#include <Wrapper.h>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>


#include <iostream>


int main(void)
{
	
	using namespace std;
	
	
	Int *ip = new Int(0);
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);
	Int *ip11 = new Int(11);
	Int *ip12 = new Int(12);
	Int *ip13 = new Int(13);
	Int *ip21 = new Int(21);
	Int *ip22 = new Int(22);
	Int *ip31 = new Int(31);
	
	
	GeneralTree *gt = new  GeneralTree(*ip);
	
	GeneralTree *gt1 = new  GeneralTree(*ip1);
	GeneralTree *gt2 = new  GeneralTree(*ip2);
	GeneralTree *gt3 = new  GeneralTree(*ip3);
	
	GeneralTree *gt11 = new  GeneralTree(*ip11);
	GeneralTree *gt12 = new  GeneralTree(*ip12);
	GeneralTree *gt13= new  GeneralTree(*ip13);
	
	GeneralTree *gt21= new  GeneralTree(*ip21);
	GeneralTree *gt22= new  GeneralTree(*ip22);
	
	GeneralTree *gt31= new  GeneralTree(*ip31);
	
	gt1->AttachSubtree(*gt11);
	gt1->AttachSubtree(*gt12);
	gt1->AttachSubtree(*gt13);
	
	gt2->AttachSubtree(*gt21);
	gt2->AttachSubtree(*gt22);
	
	gt3->AttachSubtree(*gt31);

	
	gt->AttachSubtree(*gt1);
	gt->AttachSubtree(*gt2);
	gt->AttachSubtree(*gt3);
	
	cout << "is empty?:" << gt->IsEmpty()<< endl;
	cout<<" degree:" << gt->Degree() <<endl;
	cout << "root tree key : " << gt->Key()<< endl;
	cout << "is leaf?:"<< gt->IsLeaf()<<endl;
	cout << "height:"<< gt->Height() << endl;
	
	PuttingVisitor pv(cout);

	PreOrder ppv(pv);
	
	Tree & t = dynamic_cast<Tree &> (*gt);
	cout <<endl<<"breadth first travel as following:" <<endl;
	t.BreadthFirstTraversal(pv);
	
	cout << endl;
	cout <<"Depth  first travel as following:" <<endl;
	t.DepthFirstTraversal(ppv);
	cout << endl;
	

	
	
	cout << " visit the General Tree as Iterator:"<< endl;
	
	Iterator &i = t.NewIterator();
	while(!i.IsDone()){
		Int  &g = dynamic_cast<Int &>(*i);
		cout << " ";
		g.Put(cout) ;
		++i;
	}
	cout << endl;
	
	
		cout << " after detatch sub tree do BreadthFirstTraversal : "<< endl;
	GeneralTree &gt3r =  gt->DetachSubtree(*gt3);
	
	delete &gt3r;
	t.BreadthFirstTraversal(pv);
	cout <<endl;
	
	
}

