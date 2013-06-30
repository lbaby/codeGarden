#include <ToolKits.h>
#include <Wrapper.h>
#include <BTree.h>

#include <iostream>
int main(void)
{
	
	using namespace std;
	
	cout <<"String this = this ?"<< (String("this" ) == String("this") ) <<endl;
	
	
	BTree bt(4);
	
	ReadDictionary (bt);

	 
	 #ifdef DPRINT
	 bt.printTree();
	 #endif
	 
	 	 TranslateText (bt);
	
}

