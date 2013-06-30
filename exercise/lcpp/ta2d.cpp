#include <Array2d.h>
#include <iostream>

int main(void)
{
        using namespace std;
        Array2D<int> a(4, 5);
        for(unsigned i =  0; i < 4; ++i) {
                for(unsigned j = 0; j < 5; ++j) {
                        a [i] [j] = i*10 + j;
                        cout << (a[i][j] )<<' ';
                }
                cout<<endl;
        }


}

