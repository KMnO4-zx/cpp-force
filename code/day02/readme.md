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


## Char

char 也是一种常用的整数类型。有人可能会困惑，认为 char 只用于字符。由于字符被编码为整数值， char 确实是整数类型，并且有 8 位。 char 对于英文字符来说足够宽，但不适用于中文、日文、韩文以及一些其他字符。 char16_t 和 char32_t 分别在 C++11 中被引入，用于 16 位和 32 位的范围。

以下三行代码是等效的。

```cpp
char c = 'C'; // its ASCII code is 80
char c = 80; // in decimal
char c = 0x50; // in hexadecimal
```

## Bool

bool 类型只有两个值：true 和 false。在内存中，true 被表示为 1，false 被表示为 0。

```cpp
bool b = true;
int i = b; // the value of i is 1.
```

## Float

```cpp
//float.cpp
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    float f1 = 1.2f;
    float f2 =  f1 * 1000000000000000;
    cout << std::fixed << std::setprecision(15) << f1 << endl;
    cout << std::fixed << std::setprecision(1) << f2 << endl;
    return 0;
}
```

```bash
1.200000047683716
1200000038076416.0
```

f1 被赋值为 1.2 ，然后乘以 1000000000000000 （15 个零）。我们可能会认为 f2 应该是 1200000000000000 。但如果我们以非常高的精度打印 f1 和 f2 ，我们会发现一个可怕的事实。 f2 并非我们所期望的，甚至 f1 也不完全等于 1.2 。

![alt text](./images/float.png)

float 类型 32 位浮点数，有 1 个符号位，8 个指数位和 23 个分数位。在计算机中，浮点数是以二进制形式存储的。在这种情况下，1.2 无法准确表示为二进制小数。因此，1.2 在计算机中被存储为一个近似值。当我们将这个近似值乘以 1000000000000000 时，结果也是近似值。s

32位浮点数的值由以下公式表示：  

$$
(-1)^{b_{31}} \times 2^{(b_{30}b_{29} \dots b_{23})_2 - 127} \times (1.**************)
$$  

它的最小正规数是 $\pm 1.175,494,3 \times 10^{-38}$，最大正规数是 $\pm 3.402,823,4 \times 10^{38}$。由于32位浮点数的数据范围比32位整数大得多，因此其精度是有限的，有时甚至比32位整数还差。在0到1.0之间有无数个数字。对于无限的数，我们不能使用有限长度的二进制向量来表示。只有0到1.0之间的有限个数字可以用浮点数表示，其余部分会消失在浮点数的表示空间中。根据浮点数的公式，任何二进制代码的组合都无法精确表示“1.2”，其表示空间中只有近似值“1.200000047683716”。