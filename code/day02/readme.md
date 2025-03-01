# Day 2: Data Types and Arithmetic Operators

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

另外发现一个更有趣的溢出现象：

```cpp
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
```
运行这个代码之后，输出结果如下：

```bash
56789 * 56789 unsigned c = 3224990521
56789 * 56789 unsigned long d = -1069976775
```

我本以为 `unsigned int` 和 `unsigned long int` 会有相同的结果，但是结果却不同。以下是和 Deepseek-R1 请教后的结果：

1. ​数值计算：56789 * 56789 = 3224990521。该值超过32位int的最大值（2147483647），导致溢出。

2. ​溢出后的处理：32位有符号int溢出后，结果为负数（补码形式）。具体值为-1079976775（即3224990521 - 4294967296）。

3. ​转换为unsigned int（c的值）​：负值-1079976775转换为32位无符号整数时，直接按位解释为无符号数，得到3224990521，即正确结果。

4. ​转换为unsigned long int（d的值）​：
   - unsigned long int 通常为64位。
   - 负的int值-1079976775在转换为64位有符号整数时会进行符号扩展，高位填充1，结果- 为0xFFFFFFFFB74D3329。
   - 转换为无符号整数后，该值变为18446744072639574841（即2^64 - 1079976775），导致错误。

| Integer type                    | Width in bits |
|---------------------------------|---------------|
| `char`                          | 8             |
| `short` (`short int`)           | 16            |
| `int`                           | 16 or 32      |
| `long` (`long int`)             | 32 or 64      |
| `long long` (`long long int`)   | 64            |