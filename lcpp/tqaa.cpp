#include <QueueAsArray.h>

#include <iostream>
#include <Wrapper.h>
#include <PuttingVisitor.h>



int main(void)
{
	using namespace std;
	QueueAsArray qaa(100);
	String *s = new String("string");
	qaa.Enqueue(*s);

	PuttingVisitor pv(cout);
	
	Int *i = new Int(3);
	qaa.Enqueue(*i);
	 
	qaa.Enqueue(* new Int(2));
	 qaa.Accept(pv);
	  cout <<endl;
	cout<< " head now: " << qaa.Head() <<endl;
	Object &o1 = qaa.Dequeue();
	cout<< " head now: " << qaa.Head() <<endl;
	Object &o2 = qaa.Dequeue();
	
	cout<< "member : " << o1 << " , " << o2 <<endl;
	
	delete &o2;
	

}
