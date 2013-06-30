#include <QueueAsLinkedList.h>

#include <iostream>
#include <Wrapper.h>
#include <PuttingVisitor.h>



int main(void)
{
	using namespace std;
	QueueAsLinkedList qall;
	String *s = new String("string");
	qall.Enqueue( *s);

	PuttingVisitor pv(cout);
	
	Int *i = new Int(3);
	qall.Enqueue( *i);
	 
	qall.Enqueue(* new Int(2));
	 qall.Accept(pv);
	  cout <<endl;
	cout<< " head now: " << qall.Head() <<endl;
	Object &o1 = qall.Dequeue();
	cout<< " head now: " << qall.Head() <<endl;
	Object &o2 = qall.Dequeue();
	
	cout<< "member : " << o1 << " , " << o2 <<endl;
	
	delete &o2;
	

}
