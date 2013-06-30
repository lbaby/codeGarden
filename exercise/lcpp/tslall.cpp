#include <SortedListAsLinkedList.h>
#include <Wrapper.h>
#include <PuttingVisitor.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	SortedListAsLinkedList sall;
	PuttingVisitor pv(cout);
	
	
	
	sall.Insert(* new Int(3) );
	sall.Insert(* new Int(4) );
	sall.Insert(* new Int(6) );


	
	sall.Accept(pv);
	cout <<endl << endl;
	
	Int i4(4);
	Int i3(3);
	Int i6(6);
	
	Int *ip5 = new Int(5);
	sall.InsertAfter(sall.FindPosition(i4), *ip5 );
	sall.Accept(pv);
	cout <<endl << endl;
	
	sall.InsertBefore(sall.FindPosition(i3), *new Int(2) );
	sall.Accept(pv);
	cout <<endl << endl;
	

	for (int i = 0 ; i < 5 ; i ++){
		cout << "[unsigned  ]" <<  sall[i]<<endl;
		Int ii (i + 2);
		cout << "[position  ]" <<   sall[sall.FindPosition( ii) ]  << endl;
		
	}
	
	cout << "Int i3(3) is member? == " << sall.IsMember(i3) << endl;
	
		cout << " ip5 find? "<<  sall.Find(*ip5) << endl;
	cout << "Int *ip5  is member? == " << sall.IsMember(*ip5) << endl;
	
	sall.Withdraw(*ip5);
	delete ip5;
	cout << "after draw ip5 ";
	sall.Accept(pv);
	cout <<endl << endl;
	


}
