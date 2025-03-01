#include <iostream>
#include "mul.hpp"

using namespace std;

int main() {
    int a, b, result;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    result = mul(a, b);
    cout << "The result is: " << result << endl;
    return 0;
}