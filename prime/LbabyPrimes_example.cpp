#include <iostream>
#include <iterator>
#include "LbabyPrimes.h"

using namespace std;

void Test();
template <typename IntType>
void DoJob(IntType maxNum);

int main()
{
    //Test();
    DoJob<unsigned int>(0xFFFFFFFF);

    return 0;
}

void Test()
{
    class TestingFailure {};
    
    const int maxNum = 100;
    LbabyPrimes<int> primes;
        
    try {
        try {
            primes.IsPrime(43);
            throw TestingFailure();
        }
        catch (const LbabyPrimes<int>::Unready &) { }

        primes.FindPrimes(maxNum);

        try {
            primes.IsPrime(43);
        }
        catch (const LbabyPrimes<int>::Unready &) {
            throw TestingFailure();
        }
        
        try {
            primes.IsPrime(0);
            throw TestingFailure();
        }
        catch (const LbabyPrimes<int>::Unready &) { }
        
        try {
            primes.IsPrime(101);
            throw TestingFailure();
        }
        catch (const LbabyPrimes<int>::Unready &) { }
        
        cout << "Total number of primes in the range: " << primes.GetPrimesCount() << endl;
        primes.OutputPrimes(ostream_iterator<int>(cout, " "));
        cout << endl;
    }
    catch (const TestingFailure &) {
        cout << "failed to test" << endl;
    }
}

template <typename IntType>
void DoJob(IntType maxNum)
{
    LbabyPrimes<IntType> primes;
    primes.FindPrimes(maxNum);
    cout << "Total number of primes: " << primes.GetPrimesCount() << endl;
}
