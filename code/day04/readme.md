# Day 4: 数组、字符串、结构体、联合体和枚举

## 数组
数组是一种连续分配的内存空间，用于存储固定数量的对象（数组大小不能改变）。数组的元素类型可以是任意基本类型（如 `int`、`float`、`bool` 等）、结构体、类、指针或枚举。

```cpp
#include <iostream>
using namespace std;
int main()
{
    int num_array1[5] = {34, 56}; //uninitialized array, random values 
    int num_array2[5] = {0, 1, 2, 3, 4}; //initialization

    for(int idx = 0; idx < 5; idx++)
        cout << num_array1[idx] << " ";
    cout << endl;

    for(int idx = 0; idx < 5; idx++)
        cout << num_array2[idx] << " ";
    cout << endl;

    return 0;
}
```

> 注：未定义的数组元素的值是未定义的，可能是随机值。

### 可变长度数组
如果数组的长度不是一个整型常量表达式，则该数组为可变长度数组。

```cpp
#include <iostream>
using namespace std;
int main()
{
    int num_array1[5] = {0,1}; // fixed length array, initialized to {0,1,0,0,0}  
    cout << "sizeof(num_array1) = " << sizeof(num_array1) << endl;

    int len = 0;
    while ( len < 10 )
    {
        int num_array2[len]; //variable-length array
        cout << "len = " << len;
        cout << ", sizeof(num_array2)) = " << sizeof(num_array2) << endl;
        len ++;
    }
}
```

### 未声明大小的数组
在声明时未指定数组的大小，通常用于函数参数。

```cpp
#include <iostream>
using namespace std;

// float array_sum(float *values, size_t length) // equivalent to the next line
float array_sum(float *values, size_t length)
{
    cout << sizeof(values) << endl; // 4 or 8
    float sum = 0.0f;
    for (int i = 0; i < length; i++)
    {
        sum += values[i];
    }
    return sum;
}

int main()
{
    float values[4] = {1.1f, 2.2f, 3.3f, 4.4f};
    float sum = array_sum(values, 4);

    cout << "sum = " << sum << endl;
    return 0;
}
```

### 元素访问
C/C++ 中没有边界检查。

```cpp
int array1[4] = {9, 8, 7, 6};
int array2[4];
array2 = array1; // 错误！
array2[0] = array1[0]; // 正确
array2[1] = array1[1]; // 正确
array2[2] = array1[2]; // 正确
array2[3] = array1[3]; // 正确

int num_array[5];
for (int idx = -1; idx <= 5; idx++) {
    num_array[idx] = idx * idx;
}
for (int idx = -1; idx <= 5; idx++) {
    cout << num_array[idx] << endl;
}
```

在 C++ 中，数组就是一块连续的内存。数组的下标是从 0 开始的，最大下标是 `size - 1`。一定要注意数组的边界，否则可能会访问到未定义的内存。

```cpp
#include <iostream>
using namespace std;
int main()
{
    int num_array[5]; 

    for(int idx = -1; idx <= 5; idx++) //out of bounds
        num_array[idx] = idx * idx;

    for(int idx = -1; idx <= 5; idx++) //out of bounds
        cout << "num_array[" << idx << "] = " << num_array[idx] << endl;

    return 0;
}
```

### 多维数组
多维数组在内存中是连续存储的。

```cpp
#include <iostream>
using namespace std;

// You must tell the function the bound of an array,
// otherwise, elements cannot be accessed
// if the array is a variable-length one, it may be difficult to know the bound
void init_2d_array(float mat[][3], //error, arrays of unknown bound
                    size_t rows, size_t cols)
{
    for (int r = 0; r < rows; r++)
        for(int c = 0; c < cols; c++)
            mat[r][c] =  r * c;
}

int main()
{
    int mat1[2][3] = {{11,12,13}, {14,15,16}};

    int rows = 2;
    int cols = 3;
    //float mat2[rows][cols]; //uninitialized array
    float mat2[rows][3]; //uninitialized array

    init_2d_array(mat2, rows, cols);

    // for (int r = 0; r < rows; r++)
    //     for(int c = 0; c < cols; c++)
    //         mat2[r][c] =  r * c;


    for (int r = 0; r < rows; r++)
    {
        for(int c = 0; c < cols; c++)
            cout << mat1[r][c] << " ";
        cout << endl;
    }
    return 0;
}
```

### 常量数组
常量数组的值不能被修改。

```cpp
const float PI = 3.1415926f;
PI += 1.f; // 错误

const float values[4] = {1.1f, 2.2f, 3.3f, 4.4f};
values[0] = 1.0f; // 错误

float array_sum(const float values[], size_t length) {
    float sum = 0.0f;
    for (int i = 0; i < length; i++) {
        sum += values[i]; // values[i] = 0; // 错误
    }
    return sum;
}
```

### 作为函数参数的数组
数组作为函数参数时，通常传递的是数组的指针。

```cpp
float array_sum(const float values[], size_t length);
```

## 字符串
### 数组风格的字符串和字符串类
数组风格的字符串（以空字符终止的字符串）是一系列存储在内存中的字符。

```cpp
// initchar.cpp
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char rabbit[16] = {'P', 'e', 't', 'e', 'r'};
    cout << "String length is " << strlen(rabbit) << endl;
    for(int i = 0; i < 16; i++)
        cout << i << ":" << +rabbit[i] << "(" << rabbit[i] << ")" << endl;

    char bad_pig[9] = {'P', 'e', 'p', 'p', 'a', ' ', 'P', 'i', 'g'};
    char good_pig[10] = {'P', 'e', 'p', 'p', 'a', ' ', 'P', 'i', 'g', '\0'};

    cout << "Rabbit is (" << rabbit << ")" << endl;
    cout << "Pig's bad name is (" << bad_pig << ")" << endl; 
    cout << "Pig's good name is (" << good_pig << ")" << endl; 

    char name[10] = {'Y', 'u', '\0', 'S', '.', '0'};
    cout << "(" << name << ")" << endl;
    cout << strlen(name) << endl;

    return 0;
}
```

### 字符串字面量
字符串字面量可以方便地初始化字符串。

```cpp
char name1[] = "Southern University of Science and Technology";
char name2[] = "Southern University of " "Science and Technology";
char name3[] = "ABCD"; // 数组占用多少字节？
const wchar_t s5[] = L"ABCD";
const char16_t s9[] = u"ABCD"; // C++11 起支持
const char32_t s6[] = U"ABCD"; // C++11 起支持
```

### 字符串操作和检查
- 复制：`char* strcpy(char* dest, const char* src);`
- 安全的复制：`char* strncpy(char* dest, const char* src, size_t count);`
- 连接：`char* strcat(char* dest, const char* src);`
- 比较：`int strcmp(const char* lhs, const char* rhs);`

### 字符串类
字符串类提供了更安全的字符串操作功能。

```cpp
#include <iostream>
#include <string>

using namespace std;
int main()
{
    std::string str1 = "Hello";
    std::string str2 = "SUSTech";
    std::string result = str1 + ", " + str2;

    cout << "result = " + result << endl;

    cout << "The length is " << result.length() << endl;

    cout << "str1 < str2 is " << (str1 < str2) << endl;

    cout << "str1[100] = (" << str1[100] << ")" << endl;

    return 0;
}
```

### 不同类型的字符串
- `std::string`
- `std::wstring`
- `std::u8string` (C++20 起支持)
- `std::u16string` (C++11 起支持)
- `std::u32string` (C++11 起支持)

## 结构体、联合体和枚举
### 结构体
结构体是一种由一系列成员组成的类型，成员按顺序分配内存。

```cpp
struct Student {
    char name[4];
    int born;
    bool male;
};
struct Student stu;
strcpy(stu.name, "Yu");
stu.born = 2000;
stu.male = true;

struct Student stu = {"Yu", 2000, true};
struct Student students[100];
students[50].born = 2002;
```

### 结构体填充
为了在内存中对齐数据，可能会填充一些空字节。

```cpp
struct Student1 {
    int id;
    bool male;
    char label;
    float weight;
};

struct Student2 {
    int id;
    bool male;
    float weight;
    char label;
};
```

### 结构体在 C 和 C++ 中的区别
在 C++ 中，`struct` 和 `class` 的区别主要在于默认的访问权限和继承方式。

### 联合体
联合体的声明与结构体类似，但其成员的存储空间是重叠的。

```cpp
union ipv4address {
    std::uint32_t address32;
    std::uint8_t address8[4];
};
```

### 枚举
枚举创建了一种新的类型，提供了一种替代 `const` 的方式来创建符号常量。

```cpp
enum color {WHITE, BLACK, RED, GREEN, BLUE, YELLOW, NUM_COLORS};
enum color pen_color = RED;
pen_color = color(3);
cout << "We have " << NUM_COLORS << " pens." << endl;
```

### 示例：结构体、联合体和枚举的结合使用
```cpp
struct Point {
    enum datatype type;
    union {
        std::int8_t data8[3];
        std::int16_t data16[3];
        std::int32_t data32[3];
        std::int64_t data64[3];
    };
};

size_t datawidth(struct Point pt) {
    return size_t(pt.type) * 3;
}

enum datatype {TYPE_INT8 = 1, TYPE_INT16 = 2, TYPE_INT32 = 4, TYPE_INT64 = 8};

int64_t l1norm(struct Point pt) {
    int64_t result = 0;
    switch (pt.type) {
        case TYPE_INT8:
            result = abs(pt.data8[0]) + abs(pt.data8[1]) + abs(pt.data8[2]);
            break;
        ...
    }
}
```

### 类型定义（`typedef`）
`typedef` 可以为类型创建别名，用于替代复杂的类型名称。

```cpp
typedef int myint;
typedef unsigned char vec3b[3];
typedef struct _rgb_struct { // 名称 `_rgb_struct` 可以省略
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_struct;

myint num = 32;
unsigned char color[3];
vec3b color = {255, 0, 255};
rgb_struct rgb = {0, 255, 128};
```

### 典型的 `typedef` 用法
```cpp
#ifndef _UINT8_T
#define _UINT8_T
typedef unsigned char uint8_t;
#endif /* _UINT8_T */

#if defined(_LP64)
typedef int wchar_t;
#else
typedef long wchar_t;
#endif
```