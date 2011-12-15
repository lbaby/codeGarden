#include <DequeAsArray.h>
#include <DequeAsLinkedList.h>
#include <Object.h>
#include <Wrapper.h>
#include <PuttingVisitor.h>

#include <iostream>


int main(void)
{
	using namespace std;
	
	DequeAsArray dqa(100U);
	DequeAsLinkedList dql;
	
	dqa.EnqueueHead(* new Int(2));
	dql.EnqueueHead(* new Int(2));
	
	cout<< "head: "<< dql.Head()  <<"  " << dqa.Head()<<endl;
	cout<< "tail : "<< dql.Tail()<< " " << dqa.Tail() << endl;
	
	dqa.EnqueueHead(* new Int(1));
	dql.EnqueueHead(* new Int(1));
	
	cout<< "head: "<< dql.Head()  <<"  " << dqa.Head()<<endl;
	cout<< "tail : "<< dql.Tail()<< " " << dqa.Tail() << endl;
	
	dqa.EnqueueTail(* new Int(3));
	dql.EnqueueTail(* new Int(3));
	
	cout<< "head: "<< dql.Head()  <<"  " << dqa.Head()<<endl;
	cout<< "tail : "<< dql.Tail()<< " " << dqa.Tail() << endl;
	
	PuttingVisitor pv(cout);
	
	dqa.Accept(pv);
	dql.Accept(pv);
	cout<<endl;
	
	Object &a3 = dqa.DequeueTail();
	Object &l3 = dql.DequeueTail();
	
	cout<< "head: "<< dql.Head()  <<"  " << dqa.Head()<<endl;
	cout<< "tail : "<< dql.Tail()<< " " << dqa.Tail() << endl;	
	
	Object &a1 = dqa.DequeueHead();
	Object &l1 = dql.DequeueHead();
	
	cout<< "head: "<< dql.Head()  <<"  " << dqa.Head()<<endl;
	cout<< "tail : "<< dql.Tail()<< " " << dqa.Tail() << endl;
	
	Object &a2 = dqa.DequeueHead();
	Object &l2 = dql.DequeueHead();
	
	try {
			dqa.DequeueHead();
	dql.DequeueHead();
	}
	
	catch (exception &e){
		cout << e.what() << endl;
	}
	
	delete &l1;
	delete &l2;
	delete &l3;
	
	delete &a1;
	delete &a2;
	delete &a3;
}
	

