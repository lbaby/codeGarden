#include <Matrix.h>

#include <iostream>

using namespace std;

int main(void)
{
        using namespace std;

        Matrix<int> m(4, 5);
        Matrix<int> tm(4, 5);
        Matrix<int> mt(5, 4);

        for(int i = 0; i < 4; ++i) {
                for(int j = 0; j <5; ++j) {
                        m[i][j] = i * 10 + j;
                        tm[i][j] = i * 10 + j;
                        mt[j][i] = i * 10 + j;
                }
        }

        Matrix<int> add
                (4, 5);

        add
                = m + tm;

        Matrix<int> mut(4, 4);

        mut = m * mt;

        for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 5; ++j) {
                        cout<<add
                        [i][j]<<' ';
                }
                cout<<endl;
        }


        for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                        cout<<add
                        [i][j]<<' ';
                }
                cout<<endl;
        }



}

