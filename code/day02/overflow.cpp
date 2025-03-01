//overflow.cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 56789;
    int b = 56789;
    unsigned int c = a * b;
    unsigned long int d = a * b;
    cout << "56789 * 56789 unsigned c = " << c << endl;
    cout << "56789 * 56789 unsigned long d = " << d << endl;
    return 0;
}