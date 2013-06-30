
#include <Array.h>
#include <iostream>

using namespace std;

int main(void)
{
        Array<int> ta(102400);
        Array<int> tb = ta;
        for(int i = 0 ; i < 102400 ; i++) {
                tb[i] = i;
        }

        cout<<"data is:"<< tb.Data() << endl
        <<"base is:"<< tb.Base() << endl
        <<"lenth is:"<< tb.Length()<< endl;

        for(int i = 0; i < 10 ; i++) {
                cout <<tb[i] <<'\n';
        }

        for(int i = 12400 -1 ; i > 12380 ; i--) {
                cout <<tb[i] <<'\n';
        }

        try {
                cout<<tb[102444];
        }
        catch(const out_of_range &e) {
                cout<< e.what()<<endl;
        }
        return 0;
}




