#include <LeftistHeap.h>
#include <iostream>
#include <Wrapper.h>
#include <PuttingVisitor.h>

int main(void)
{
	LeftistHeap lh;
		Int  *ip1 = new Int(1);
	Int  *ip2 = new Int(2);
	Int  *ip3 = new Int(3);
	Int  *ip4 = new Int(4);
	Int  *ip5 = new Int(5);
	Int  *ip6 = new Int(6);
	Int  *ip7 = new Int(7);
	
	
	using namespace std;
	
	PuttingVisitor pv(cout);
	
	lh.Enqueue(*ip4);
	lh.Enqueue(*ip5);
	lh.Enqueue(*ip6);
	lh.Enqueue(*ip7);
	lh.Enqueue(*ip1);
	lh.Enqueue(*ip2);
	lh.Enqueue(*ip3);
	
	lh.Accept(pv);
	
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	cout<<lh.DequeueMin ()<<endl;
	
	
}
