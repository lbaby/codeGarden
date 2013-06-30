#include <NaryTree.h>
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
	
	
	NaryTree *nt = new  NaryTree(3, *ip);
	

	
	NaryTree *nt1 = new NaryTree(3, *ip1); 
	NaryTree *nt2 = new NaryTree(3, *ip2); 
	NaryTree *nt3 = new NaryTree(3, *ip3); 
	
	NaryTree *nt11 = new NaryTree(3, *ip11); 
	NaryTree *nt12 = new NaryTree(3, *ip12); 
	NaryTree *nt13 = new NaryTree(3, *ip13); 
	
	NaryTree *nt21= new  NaryTree(3, *ip21);
	NaryTree *nt22= new  NaryTree(3, *ip22);
	
	NaryTree *nt31= new  NaryTree(3, *ip31);
	
	nt1->AttachSubtree(0, *nt11);
	nt1->AttachSubtree(1, *nt12);
	nt1->AttachSubtree(2, *nt13);
	
	nt2->AttachSubtree(0,*nt21);
	nt2->AttachSubtree(1, *nt22);
	
	nt3->AttachSubtree(0, *nt31);

	
	nt->AttachSubtree(0, *nt1);
	nt->AttachSubtree(1, *nt2);
	nt->AttachSubtree(2, *nt3);
	
	cout << "is empty?:" << nt->IsEmpty()<< endl;
	cout<<" degree:" << nt->Degree() <<endl;
	cout << "root tree key : " << nt->Key()<< endl;
	cout << "is leaf?:"<< nt->IsLeaf()<<endl;
	cout << "height:"<< nt->Height() << endl;
	
	PuttingVisitor pv(cout);

	PreOrder ppv(pv);
	
	Tree & t = dynamic_cast<Tree &> (*nt);
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
	NaryTree &nt3r =  nt->DetachSubtree(2);
	
	delete &nt3r;
	t.BreadthFirstTraversal(pv);
	cout <<endl;
	
	
}

