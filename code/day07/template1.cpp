#include <iostream>
#include <typeinfo>

using namespace std;

template<typename T>
T sum(T x, T y)
{
    cout << "The input type is " << typeid(T).name() << endl;
    return x + y;
}

// Explicitly instantiate
template double sum<double>(double, double);
template float sum<>(float, float);
template int sum (int, int);


int main()
{
    auto val = sum(4.1, 5.2);
    auto val2 = sum(4.5f, 5.6f);
    auto val3 = sum(1, 2);
    cout << val << "\n" << val2 << "\n" << val3 << endl;
    return 0;
}