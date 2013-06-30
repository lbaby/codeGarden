#include <iostream>
#include <LinkedList.h>
#include <string>


int main(void)
{
        using namespace std;
        string astr("this is a test -> ");
        LinkedList<string> tll;

        for(int i = 0 ; i < 10; ++i) {
                char tmp[4]={0};
                tmp [0] = 'a' +i;
                string istr = astr + string(tmp);
                tll.Append(istr);
        }

        tll.Prepend("\" this \"");
        tll.Append("\"that\" ");

        const ListElement<string> *ptr = tll.Head();
        while (ptr) {
                cout<< ptr->Datum() <<endl;
                ptr = ptr->Next();
        }


        cout << tll.Head()->Datum()<<endl;
        cout << tll.Tail()->Datum()<<endl;
        cout << "the list is empty  is "<<tll.IsEmpty()<<endl;
        cout << "the first is "<<tll.First()
        << "and the last is "<<tll.Last()
        << endl;

        ptr = tll.Head();
        ptr = ptr->Next()->Next();
        tll.InsertAfter(ptr, "insert after");
        tll.InsertBefore(ptr, "inster before");
        tll.Extract("this is a test -> e");
        ptr = tll.Head();

        while (ptr) {
                cout<< ptr->Datum() <<endl;
                ptr = ptr->Next();
        }


        tll.Purge();
        cout<<"empty: "<<tll.IsEmpty();
        try {
        	tll.InsertAfter(0, "");
        }
        
        catch (exception &e){
        	cout << e.what();
        }



}

