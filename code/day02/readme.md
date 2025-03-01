# Day2: Data Types and Arithmetic Operators

## Int

```cpp
//init.cpp
#include <iostream>
using namespace std;
int main()
{
    int num1; //bad: uninitialized variable
    int num2; //bad: uninitialized variable
    cout << "num1 = " << num1 << endl;
    cout << "num2 = " << num2 << endl;
}
```

```bash
g++ ./init.cpp -o a.o && ./a.o && rm -rf a.o
```
未初始化的变量 num1 和 num2 。它们在声明后立即打印出来。但是在不同的电脑上打印出来的数值是不一样的。我的电脑上如下所示：

```bash
num1 = 1
num2 = -174636976
```

### Overflow

```cpp
//overflow.cpp
#include <iostream>
using namespace std;

int main()
{
    int a = 56789;
    int b = 56789;
    int c = a * b;
    cout << "c = " << c << endl;
    return 0;
}
```

```bash
g++ ./overflow.cpp -o a.o && ./a.o && rm -rf a.o
```

`int` 类型在大多数系统中是一个 32 位有符号整数，其最大值为 2,147,483,647。当计算 $56789 \times 56789 = 3,224,990,521$ 时，结果超出了 `int` 类型的最大范围，导致整数溢出。溢出后，结果被截断为适合 32 位的值，并解释为有符号整数，最终输出错误的结果 `-1069976775`。
