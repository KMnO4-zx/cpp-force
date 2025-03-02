# Day 3: 分支和循环语句

## `if` 语句

`if` 语句可以根据条件选择性地执行代码，是编程中常用的语句之一。它的执行依赖于布尔表达式。例如，在以下代码中，当变量 `num` 的值小于 `5` 时，程序会执行并打印 “The number is less than 5.”（数字小于5）。

```cpp
// if.cpp
int num = 2;
// 可能会改变 num 值的操作
if (num < 5)
    cout << "The number is less than 5." << endl;
```

如果需要执行的是复合语句，则必须用大括号 `{}` 包裹。即使只有一行代码，也可以使用大括号。
```cpp
if (num == 5)
{
    cout << "The number is 5." << endl;
    // 其他代码
}
```

当 `if` 后面的条件不满足时，会执行 `else` 语句。

```cpp
if (num == 5)
{
    cout << "The number is 5." << endl;
}
else
{
    cout << "The number is not 5." << endl;
}
```

如果有多个条件需要判断，可以使用 `else if`，如下所示。首先会判断第一个条件 `num < 5`，然后是第二个条件 `num > 10`。如果没有匹配的条件，则执行 `else` 语句。需要注意的是，如果第一个条件为真，则不会继续判断 `else if` 中的第二个条件。

```cpp
if (num < 5)
    cout << "The number is less than 5." << endl;
else if (num > 10)
    cout << "The number is greater than 10." << endl;
else
    cout << "The number is in range [5, 10]." << endl;
```

`else` 会与最近的 `if` 关联。在以下代码中，`else` 是与 `if(num < 5)` 关联的，而不是 `if(num < 10)`。虽然这段代码没有语法错误，但一些足够智能的编译器可能会发出警告，因为这可能会让读者感到困惑。

```cpp
if(num < 10)
    if(num < 5)
        cout << "The number is less than 5" << endl;
    else
        cout << "Where I'm?" << endl;
```

为了使源代码更容易理解，建议使用大括号和缩进格式化代码，如下所示。

```cpp
if(num < 20)
{
    if(num < 5)
        cout << "The number is less than 5" << endl;
    else
        cout << "Where I'm?" << endl;
}
```

## `? :` 运算符

三元条件运算符 `? :` 也常用于简化一些 `if else` 语句。我们先来看以下代码。变量 `factor` 的值会根据 `isPositive` 的条件而有所不同。

```cpp
// ternary.cpp
bool isPositive = true;
int factor = 0;
// 可能会改变 isPositive 值的操作
if(isPositive)
    factor = 1;
else
    factor = -1;
```

在上述程序中，`if else` 语句占用了4行代码。这4行代码可以用一个三元条件运算符 `? :` 替代。

```cpp
factor = isPositive ? 1 : -1;
```

如果 `?` 前面的条件为真，则值为 `?` 和 `:` 之间的表达式；否则，值为 `:` 后面的表达式。

在某些情况下，上述代码甚至可以简化为一个没有跳转语句的表达式。在由 `if`、`? :`、`for`、`while` 等编译而成的指令中，存在跳转语句。与它们不同的是，以下代码不包含跳转语句。由于 `isPositive` 是布尔类型，并且可以隐式转换为 `int`，因此 `if else` 的条件赋值可以转换为单个赋值。这可能更高效，至少不会比 `if else` 效率低。有时，C/C++ 编译器可能会通过将 `if else` 转换为以下风格的语句来优化生成的二进制可执行代码。不过，并非所有 `? :` 语句都能转换为这种风格。

```cpp
factor = (isPositive) * 2 - 1;
```

## 条件表达式

在 `if` 或 `else if` 后面是一个条件表达式，例如 `num < 5`。它应该是一个可以转换为 `bool` 的表达式，可以是关系表达式、逻辑表达式或它们的组合。

```cpp
if (num < 5)
    cout << "The number is less than 5. " << endl;
```

### 关系表达式

以下是6种关系（比较）运算符。关系表达式的值为 `true` 或 `false`，也可以将它们视为 `1` 或 `0`。即使在某些编程语言（如 Java）中，`true` 与 `1` 不同，但在 C 或 C++ 中，可以认为 `true` 等同于 `1`，`false` 等同于 `0`。

| 运算名称 | 示例 |
|----------|------|
| 等于     | `a == b` |
| 不等于   | `a != b` |
| 小于     | `a < b` |
| 大于     | `a > b` |
| 小于等于 | `a <= b` |
| 大于等于 | `a >= b` |

### 逻辑表达式

以下是3种逻辑运算符。在逻辑表达式中，操作数应为布尔值。如果不是，则会隐式转换为 `bool`。

| 运算符名称 | 符号运算符 | 关键字运算符 | 示例 |
|------------|------------|--------------|------|
| 非         | `!`        | not          | `!a`, `not a` |
| 与         | `&&`       | and          | `a && b`, `a and b` |
| 或         | `\|\|`       | or           | `a \|\| b`, `a or b` |

需要注意的是，这3种逻辑运算符的优先级不同。`not` 的优先级最高，其次是 `and`，`or` 的优先级最低。

### 非布尔表达式

如果 `if` 语句中的条件表达式不是布尔类型，它们会隐式转换为 `bool`。这在 `for`、`while` 和 `switch` 语句的条件中也是如此。如果条件表达式的值是 `char`、`int`、`long`、`float` 或 `double`，非零值将被转换为 `true`，其余值将被转换为 `false`。

以下代码在语法上是正确的，但不推荐使用。使用 `count == 0` 或 `(count < FLT_EPSILON) && (count > -FLT_EPSILON)` 会更好。

```cpp
float count = 0.2f; 
if (count) // 不推荐使用浮点数
    cout << "There are some." << endl;
```

指针（本质上是一种无符号整数）也可以用在条件表达式中。以下代码中的 `(!p)` 等同于 `(p == NULL)`。

```cpp
int * p = new int[1024];
if (!p) // 如果(p == NULL)
    cout << "Memory allocation failed." << endl;
```

### 条件表达式中的陷阱

在 `if` 语句、`while` 循环或 `for` 循环中，一定要小心不要将 `==` 错误地写成 `=`。这是初学者常见的错误。以下代码是一个无限循环。

```cpp
bool flag = false;
// 执行某些操作 ...
if (flag = true) // 错误！
{
    // 执行某些操作
}
```

表达式 `3 + 4`、`a + b` 和 `a == b` 都有值。`a = b` 也是一个表达式，其值是 `a`，它被赋值为 `b` 的值。因此，`if(flag = true)` 等同于 `if(true)`，无论 `flag` 的值是什么，都会执行语句体。

如果你理解 `a = b` 是一个表达式并且有值，那么理解以下代码中的 `int m = (b = 8);` 也很容易。它的意思是 `m` 被赋值为 `(b = 8)` 的值。

```cpp
int b = 0;
int m = (b = 8);
```

## `while` 循环

`while` 循环的语法如下。如果条件表达式为 `true`，则执行循环体。

```cpp
while(expression)
{
    //...
}
```

在以下示例中，变量 `num` 被初始化为 `10`。由于 `num` 是 `10`，条件 `num > 0` 为 `true`。然后执行循环体，执行 `num--` 后，`num` 变为 `9`。循环体将被执行10次，直到 `num` 为 `0`。

```cpp
// while.cpp
#include <iostream>
using namespace std;
int main()
{
    int num = 10;
    while(num > 0)
    {
        cout << "num = " << num << endl;
        num--;
    }
}
```

`while` 循环在每次迭代之前都会进行测试。还有一种 `do-while` 循环，它在每次迭代之后进行测试。以下 `do-while` 循环的行为与前面的 `while` 循环相同。

```cpp
int num = 10;
do
{
    cout << "num = " << num << endl;
    num--;
} while (num > 0);
```

但要注意，即使条件表达式为 `false`，`do-while` 循环的循环体也会在第一次迭代中被执行。例如，以下代码会打印一行。

```cpp
int num = 0; // 条件为 false
do
{ // 但在第一次迭代中仍会执行循环体
    cout << "num = " << num << endl;
    num--;
} while (num > 0);
```

以上代码的输出为：
```console
num = 0
```

### `break` 语句

`break` 语句会在执行时终止循环，循环体的剩余部分也不会被执行。

```cpp
int num = 10;
while (num > 0)
{
    if (num == 5)
        break;
    cout << "num = " << num << endl;
    num--;
}
// 在执行 `break` 后跳转到这里
```

### `continue` 语句

`continue` 语句也会改变循环的执行流程，但它不会终止循环。程序会跳过循环体的剩余部分，继续执行下一次迭代。在以下示例中，不会打印 `num = 5`，但会打印 `num = 4`。真的吗？请运行代码检查是否一切正常。

```cpp
int num = 10;
while (num > 0)
{
    if (num == 5)
        continue; // 不会打印 "num = 5"
    cout << "num = " << num << endl;
    num--;
}
```

## `for` 循环

`for` 循环的语法如下。`for` 关键字后面有初始化子句、条件表达式和迭代表达式。

```cpp
for (init-clause; cond-expression; iteration-expression)
    loop-statement
```

以下代码展示了 `for` 循环的用法。变量 `i` 被初始化为 `1`，每次迭代中通过 `i++` 增加 `i` 的值。循环会一直执行，直到条件 `i < 10` 变为 `false`。

```cpp
int sum = 0;
for(int i = 0; i < 10; i++)
{
    sum += i;
    cout << "Line " << i << endl;
}
cout << "sum = " << sum << endl;
```

前面的 `for` 循环可以转换为 `while` 循环，如下所示。这两段代码的唯一区别是 `i` 的作用域。在前面的例子中，`i` 的作用域在 `for` 循环体内。但在 `while` 循环中，`i` 是在循环体外声明的。

```cpp
int sum = 0;
int i = 0; // 把初始化子句放在这里
while(i < 10) // while 后面是条件表达式
{
    sum += i;
    cout << "Line " << i << endl;
    i++; // 把迭代表达式放在这里
}
cout << "sum = " << sum << endl;
```

`while` 循环也可以转换为 `for` 循环，如下所示。

```cpp
while(num > 0)
{
    cout << "num = " << num << endl;
    num--;
}
```

```cpp
for(; num > 0; )
{
    cout << "num = " << num << endl;
    num--;
}
```

有些人可能会好奇，前面的 `for` 循环没有初始化子句和迭代表达式。实际上，即使条件表达式也可以省略，如下所示。

```cpp
for(; ; )
{
    if (num <= 0)
        break;
    cout << "num = " << num << endl;
    num--;
}
```

`break` 和 `continue` 在 `for` 循环中的行为与 `while` 循环相同，这里不再赘述。

## `goto` 语句

`goto` 语句可以使程序跳转到指定位置。过多使用 `goto` 语句可能会破坏程序的执行流程，因此不推荐使用。它最常用于错误处理。在函数 `mysquare()` 中，声明了一个标签 `EXIT_ERROR`。如果参数不符合要求，程序会使用 `goto` 跳转到 `EXIT_ERROR` 标签处，那里是错误处理代码。

`goto` 语句在 Linux 内核函数中广泛使用，这些函数是用 C 语言编写的。这些函数通常从多个位置退出，并且需要执行一些通用操作，例如清理。但在 C++ 中，更常用的是异常处理，这将在后续章节中介绍。

```cpp
//goto.cpp
float mysquare(float value)
{
    float result = 0.0f;
    if(value >= 1.0f || value <= 0)
    {
        cerr << "The input is out of range." << endl;
        goto EXIT_ERROR;
    }
    result = value * value;
    return result;
EXIT_ERROR:
    // 执行一些操作，例如关闭文件
    return 0.0f;
}
```

## `switch` 语句

`switch` 语句可以根据表达式的值执行多个语句中的某一个。`switch` 后面的表达式是 `input_char`，如下所示。一些初学者可能会忘记 `break`，这会导致执行后续语句。如果将 `switch` 理解为 `if - else if - else` 的形式，很容易遗漏 `break`。实际上，可以认为 `case` 定义了许多入口，`switch` 的工作方式类似于 `goto`。执行将从匹配的 `case` 入口开始，直到遇到 `break`。

```cpp
//switch.cpp
switch (input_char)
{
    case 'a':
    case 'A':
        cout << "Move left." << endl;
        break;
    case 'd':
    case 'D':
        cout << "Move right." << endl;
        break;
    default: 
        cout << "Undefined key." << endl;
        break;
}
```

## 练习

* 请使用 Makefile 管理多个源文件。你可以使用 `make` 来编译和链接，使用 `make clean` 来删除所有生成的文件。

---