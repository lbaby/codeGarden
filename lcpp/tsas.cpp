#include <iostream>
#include <StackAsArray.h>

#include <PuttingVisitor.h>



int main(void)
{
	using namespace std;

	StackAsArray stack(5);
	stack.Push(*new Int(1) );
	stack.Push(*new Int(2) );
	stack.Push(*new Int(3) );

	Iterator &i = stack.NewIterator();

	while ( !i.IsDone() ){
		cout << *i <<endl;
		++i;
	}
	delete &i;
	
	PuttingVisitor ptocout(cout);
	
	stack.Accept(ptocout);

	Object &top1 = stack.Top();
	Object &i1 = stack.Pop() ;

	Object &top2 = stack.Top();
	Object &i2 = stack.Pop() ;

	Object &top3 = stack.Top();
	Object  &i3 = stack.Pop() ;
	
	cout<<endl
	 <<i1 << " top :" << top1 << endl
	 << i2 << " top :" << top2 <<endl 
	 <<i3 << " top :" << top3 <<endl;
	 
	 delete &i1;
	 delete &i2;
	 delete &i3;
	 
	 stack.Push(*new Int(3) );
	 stack.Push(*new Int(3) );
	 stack.Push(*new Int(3) );
	 stack.Push(*new Int(3) );
	

	

}

