#include <BinomialQueue.h>
#include <PuttingVisitor.h>
#include <Wrapper.h>

#include <iostream>


int main(void)
{
	using namespace std;
	BinomialQueue bq;
	
	Int  *ip1 = new Int(1);
	Int  *ip2 = new Int(2);
	Int  *ip3 = new Int(3);
	Int  *ip4 = new Int(4);
	Int  *ip5 = new Int(5);
	Int  *ip6 = new Int(6);
	Int  *ip7 = new Int(7);

	PuttingVisitor pv(cout);
	
	bq.Enqueue(*ip4);
	bq.Enqueue(*ip5);
	bq.Enqueue(*ip6);
	bq.Enqueue(*ip7);
	bq.Enqueue(*ip1);
	bq.Enqueue(*ip2);
	bq.Enqueue(*ip3);
	
	cout<<bq.FindMin()<<endl;
	
	bq.Accept(pv);
	cout<<bq.DequeueMin ()<<endl;
	cout<<bq.DequeueMin ()<<endl;
	cout<<bq.DequeueMin ()<<endl;
	cout<<bq.DequeueMin ()<<endl;
	
	
}
