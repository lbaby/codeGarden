#include <ChainedHashTable.h>

#include <Wrapper.h>
#include <PuttingVisitor.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	ChainedHashTable cht(100);
	
	cht.Insert(* new Int(1));
	Int * ip1 = new Int(1);
	Int i1 (1);
		cht.Insert(* ip1);
	cht.Insert(* new Int(2));
	
	cht.Insert(* new Int(3));
	
	cht.Insert(* new Int(4));
	
		
	Int i4(4);
	PuttingVisitor pv(cout);
	
	cht.Accept(pv);
	
	cout << '\n'<<endl;
	
	cout << "i4 Found? == " << cht.Find(i4)<< endl;
	cout <<"ip1 IsMember?== " << cht.IsMember(*ip1)<<endl;
	
	cout <<"i1 IsMember?== " << cht.IsMember(i1)<<endl;
	
	

	
	cht.Withdraw(cht.Find(i4));
	cout<< "After withdraw i4: ";
		
	cht.Accept(pv);
	
	cout << '\n'<<endl;
	
		
	
	
	
}
