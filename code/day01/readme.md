# Day 1: Introduction to C++

## Hello world

```cpp
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    for (const string& world : meg) {
        cout << world << " ";
    };

    cout << endl;
}
```

> `string&` 是引用的意思，只是引用后面的变量，不会创建新的变量，`const` 是常量的意思，表示这个变量是只读的，不能修改。

使用 g++ 以下命令编译代码可以会遇到一点问题，如下所示：

```bash
g++ hello.cpp -o hello.o
```

如下会遇到这样的报错：

```bash
hello.cpp:8:23: error: expected ';' at end of declaration
    8 |     vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};
      |                       ^
      |                       ;
hello.cpp:10:30: warning: range-based for loop is a C++11 extension [-Wc++11-extensions]
   10 |     for (const string& world : msg) {
      |                              ^
1 warning and 1 error generated.
```

由于源文件使用的是 C++11 标准，而编译器的默认设置 g++ 可能低于 C++11，您可能会收到错误信息。通过添加选项 --std=c++11 ，您应该可以通过 g++ hello.cpp --std=c++11 成功编译源文件。

```bash
g++ hello.cpp -o hello.o --std=c++11

./hello.o
```

OUT:
```bash
Hello C++ World from VS Code and the C++ extension!
```


## Compile and Link

以一个简单的乘法程序为例，编写两个文件，一个是头文件，一个是源文件。

```cpp
// mul.cpp
#include "mul.hpp"

int mul(int a, int b) {
    return a * b;
}
```

```cpp
// mul.hpp 头文件
#pragma once

int mul(int a, int b);
```

```cpp
// main.cpp
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
```

可以使用如下命令编译和链接这两个文件：

```bash
g++ main.cpp mul.cpp -o main.o --std=c++11
```

但如果你有很多文件需要连接时，以上命令就会很麻烦，也可以使用其他命令，如下：

```bash
g++ -c main.cpp -o main.o --std=c++11
g++ -c mul.cpp -o mul.o --std=c++11
g++ main.o mul.o -o example.o --std=c++11
```

以上命令分别编译 main.cpp 和 mul.cpp 生成 main.o 和 mul.o 文件，然后链接这两个文件生成可执行文件 example.o。如果你不想逐个输入命令，可以使用 Makefile 保存编译和链接的规则，然后一个命令 make 可以帮助你完成所有操作。

```makefile
# Makefile
main.o: main.cpp
    g++ -c main.cpp -o main.o --std=c++11
    g++ -c mul.cpp -o mul.o --std=c++11
    g++ main.o mul.o -o example.o --std=c++11
```

## Preprocessor and Macros

```cpp
#define PI 3.14
double len(double r)
{
    return 2.0 * PI * r;
}
```

但如果你将 `PI` 定义为 `#define PI 2.14+1.0` ，虽然代码并不会报错，但是结果可能不是你想要的，因为宏定义只是简单的替换，不会进行计算。

```cpp
#define PI 2.14+1.0
double len(double r)
{
    return 2.0 * PI * r;
}
```

> 代码将返回 `2.0 * 2.14+1.0 * r`

也可以定义一个函数

```cpp
#define MAX(a,b) (((a)>(b))?(a):(b))

int main()
{
    //...
    float a = 2.0f;
    float b = 3.0f;
    float m;
    m = MAX(a, b);
    //...
}
```

## Command Line Arguments

`argc` 表示命令行参数的数量（包括程序名本身）。`argv` 存储所有命令行参数的字符串数组，包括程序名本身。

```cpp
// argument.cpp
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
    cout << "Number of arguments: " << argc << endl;
    for (int i = 0; i < argc; i++) {
        cout << i << ": " << argv[i] << endl;
    }
    return 0;
}
```

OUT
```bash
Number of arguments: 4
0: ./argument.o
1: hello.cpp
2: -o
3: hello
```

