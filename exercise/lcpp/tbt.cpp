#include <BinaryTree.h>
#include <Wrapper.h>
#include <PrePostVisitor.h>
#include <PuttingVisitor.h>



#include <iostream>


int main(void)
{
	using namespace std;
	
	Int *ip1 = new Int(1);
	Int *ip2 = new Int(2);
	Int *ip3 = new Int(3);
	Int *ip4 = new Int(4);
	Int *ip5 = new Int(5);
	Int *ip6 = new Int(6);
	Int *ip7 = new Int(7);
	
	BinaryTree *bt4 = new BinaryTree(*ip4);
	
	BinaryTree *bt1 = new BinaryTree();
	
	bt1->AttachKey(*ip1);
	
	BinaryTree *bt2 = new BinaryTree(*ip2);
	
	BinaryTree *bt3 = new BinaryTree(*ip3);
	
	bt2->AttachLeft(*bt1);
	bt2->AttachRight(*bt3);
	bt4->AttachLeft(*bt2);
	
	BinaryTree *bt5 = new BinaryTree(*ip5);
	BinaryTree *bt6 = new BinaryTree(*ip6);
	BinaryTree *bt7 = new BinaryTree(*ip7);
	
	bt6->AttachLeft(*bt5);
	bt6->AttachRight(*bt7);
	
	bt4->AttachRight(*bt6);
		
		
	cout << "is empty?:" << bt4->IsEmpty()<< endl;
	cout<<" degree:" << bt4->Degree() <<endl;
	cout << "root tree key : " << bt4->Key()<< endl;
	cout << "is leaf?:"<< bt4->IsLeaf()<<endl;
	cout << "height:"<< bt4->Height() << endl;
	cout << "degree is :" << bt4->Degree() << endl;
	
	PuttingVisitor pv(cout);
	PreOrder po (pv);
	bt4->DepthFirstTraversal(po);
	
	Tree & t = dynamic_cast<Tree &> (*bt4);
	cout <<endl<<"breadth first travel as following:" <<endl;
	t.BreadthFirstTraversal(pv);
	
	cout << endl;
	
	
}
