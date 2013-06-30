#include <BinaryHeap.h>
#include <iostream>
#include <Wrapper.h>
#include <PuttingVisitor.h>



int main(void)
{
	BinaryHeap  bh(100);
	Int  *ip1 = new Int(1);
	Int  *ip2 = new Int(2);
	Int  *ip3 = new Int(3);
	Int  *ip4 = new Int(4);
	Int  *ip5 = new Int(5);
	Int  *ip6 = new Int(6);
	Int  *ip7 = new Int(7);
	
	
	using namespace std;
	
	PuttingVisitor pv(cout);
	
	bh.Enqueue(*ip4);
	bh.Enqueue(*ip5);
	bh.Enqueue(*ip6);
	bh.Enqueue(*ip7);
	bh.Enqueue(*ip1);
	bh.Enqueue(*ip2);
	bh.Enqueue(*ip3);
	
	bh.Accept(pv);
	
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	cout<<bh.DequeueMin ();
	
	
	
	
	
}
