#include <Polynomial.h>
#include <PuttingVisitor.h>
#include <Term.h>


#include <iostream>

int main(void)
{
	using namespace std;
	
	Polynomial p;
	
	PuttingVisitor pv(cout);
	
	p.Insert( * new Term(1.1f, 1) );
	p.Insert (* new Term( 2.2f, 2) );
	p.Insert (* new Term( 3.3f, 3) );
	

	
	p.Accept(pv);
	cout << endl << endl;
	

	Polynomial q = p;
	
	p.Insert (* new Term( 4.4f, 4) );

	q.Accept(pv);
	cout << endl << endl;
	
	Polynomial sum = p + q;
	
	sum.Accept(pv);
	
	
	 
	
}

