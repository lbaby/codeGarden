#include <OpenScatterTable.h>

#include <Wrapper.h>
#include <PuttingVisitor.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	OpenScatterTable cst(100);
	
	cst.Insert(* new Int(1));
	Int * ip1 = new Int(1);
	Int i1 (1);
		cst.Insert(* ip1);
	cst.Insert(* new Int(2));
	
	cst.Insert(* new Int(3));
	
	cst.Insert(* new Int(23413242));
	cst.Insert(* new Int(23413242));
		
	Int i4(23413242);
	PuttingVisitor pv(cout);
	
	cst.Accept(pv);
	
	cout << '\n'<<endl;
	
	cout << "i4 Found? == " << cst.Find(i4)<< endl;
	cout <<"ip1 IsMember?== " << cst.IsMember(*ip1)<<endl;
	
	cout <<"i1 IsMember?== " << cst.IsMember(i1)<<endl;
	
	

	
	cst.Withdraw(cst.Find(i4));
	cout<< "After withdraw i4: ";
		
	cst.Accept(pv);
	
	cout << '\n'<<endl;
	
		
	
	
	
}
