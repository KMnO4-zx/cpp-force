# Day 6: Functions

### 为什么需要函数？
- 一个复合语句可能需要多次执行。  
- 你可以将它们复制多次，但……  

```cpp
struct Matrix {
    size_t rows; 
    size_t cols; 
    float *pData;
};
Matrix matA; 
float maxa = FLT_MIN; 
for(size_t r = 0; r < matA.rows; r++)
    for (size_t c = 0; c < matA.cols; c++) {
        float val = matA.pData[r * matA.cols + c]; 
        maxa = (maxa > val ? maxa : val);
    }
```
**nofunction.cpp**

### 使用函数的好处
- 我们可以将复合语句放入一个函数中。  

```cpp
float matrix_max(struct Matrix mat) {
    float max = FLT_MIN; 
    for(size_t r = 0; r < mat.rows; r++)
        for (size_t c = 0; c < mat.cols; c++) {
            float val = mat.pData[r * mat.cols + c]; 
            max = (max > val ? max : val);
        }
    return max;
}
float maxa = matrix_max(matA); 
float maxb = matrix_max(matB); 
float maxc = matrix_max(matC);
```

### 一个问题
- 如果 `Matrix::pData` 是 `NULL` 或无效值，如何让调用函数知道？  
- 应该首先检查指针！  

```cpp
float matrix_max(struct Matrix mat) {
    float max = FLT_MIN; 
    for(size_t r = 0; r < mat.rows; r++)
        for (size_t c = 0; c < mat.cols; c++) {
            float val = mat.pData[r * mat.cols + c]; 
            max = (max > val ? max : val);
        }
    return max;
}
```

### 函数应该放在哪里？选项 1
```cpp
// draw.cpp
// 函数必须在调用前定义
bool drawLine(int x1, int y1, int x2, int y2) {
    // 源代码
    return true;
}
bool drawRectangle(int x1, int y1, int x2, int y2) {
    // 一些计算
    drawLine(...); 
    drawLine(...); 
    drawLine(...); 
    drawLine(...);
    return true;
}
```

### 函数应该放在哪里？选项 2
```cpp
// draw.cpp
// 首先声明，可以省略参数名称
bool drawLine(int x1, int y1, int x2, int y2);
bool drawRectangle(int x1, int y1, int x2, int y2) {
    // 一些计算
    drawLine(...); 
    drawLine(...); 
    drawLine(...); 
    drawLine(...);
    return true;
}
// 稍后定义
bool drawLine(int x1, int y1, int x2, int y2) {
    // 源代码
    return true;
}
```

### 函数应该放在哪里？选项 3
```cpp
// draw.cpp
#include <draw.h>
bool drawRectangle(int x1, int y1, int x2, int y2) {
    // 一些计算
    drawLine(...); 
    drawLine(...); 
    drawLine(...); 
    drawLine(...);
    return true;
}
// 稍后定义
bool drawLine(int x1, int y1, int x2, int y2)
```

```cpp
// draw.h
#ifndef __DRAW_H__
#define __DRAW_H__
bool drawLine(int x1, int y1, int x2, int y2);
bool drawRectangle(int x1, int y1, int x2, int y2);
#endif
```

```cpp
// main.cpp
#include <draw.h>
int main() {
    // ...
    drawRectangle(10, 20, // ...
}
```

### 函数是如何被调用的？
- 调用栈可以存储程序中活动函数的信息：  
  - 存储函数调用后程序返回的地址  
  - 存储寄存器  
  - 存储局部变量  
- // 执行被调用函数的工作  
- 恢复寄存器  
- 恢复局部变量  
- 存储函数返回结果  
- 跳转到返回地址  

### 函数调用的代价

### 函数参数
- 参数是传递到函数中的“数据”的符号名称。  
- 有两种方式将数据传递到函数中：  
  - 按值传递  
  - 按引用传递  

#### 按值传递：基本类型
- 参数是原始变量的副本。  

```cpp
int foo(int x) { // x 是副本
    x += 10; 
    return x;
}
int main() {
    int num1 = 20; 
    int num2 = foo(num1);
    return 0;
}
```
`num1` 在 `foo()` 中会被改变吗？

#### 按值传递：指针
- 有什么区别？  

```cpp
int foo(int *p) {
    (*p) += 10; 
    return *p;
}
int main() {
    int num1 = 20; 
    int *p = &num1; 
    int num2 = foo(p); 
    return 0;
}
```
这仍然是按值传递（地址！）——地址的副本  

#### 按值传递：结构体
- 结构体参数呢？  

```cpp
struct Matrix {
    int rows; 
    int cols; 
    float *pData;
};
float matrix_max(struct Matrix mat) {
    float max = FLT_MIN; 
    for(int r = 0; r < mat.rows; r++)
        for (int c = 0; c < mat.cols; c++) {
            float val = mat.pData[r * mat.cols + c]; 
            max = (max > val ? max : val);
        }
    return max;
}
```

#### 按值传递：结构体
```cpp
matA
pData
cols:4
rows:3
mat
pData
cols:4
rows:3
. . .
Matrix matA = {3,4}; 
matrix_max(matA);
float matrix_max(struct Matrix mat) {
    float max = FLT_MIN; 
    for(size_t r = 0; r < mat.rows; r++)
        for (size_t c = 0; c < mat.cols; c++) {
            float val = mat.pData[r * mat.cols + c]; 
            max = (max > val ? max : val);
        }
    return max;
}
```

#### 按值传递：结构体
- 如果结构体非常大，例如 1KB。  
- 复制将占用 1KB 内存，并且复制过程耗时。  

#### C++ 中的引用
- 引用存在于 C++ 中，而不是 C 中。  
- 引用是已经存在的变量/对象的别名。  

```cpp
int num = 0; 
int &num_ref = num;
num 0
0xABCDEF03
0xABCDEF02
0xABCDEF01
0xABCDEF00
num,
num_ref num_ref = 10; 10
```

#### C++ 中的引用
- 对象 `matA` 的引用  
```cpp
pData
cols:4
rows:3
.
matA
matA_ref
struct Matrix {
    size_t rows; 
    size_t cols; 
    float *pData;
};
Matrix matA = {3,4}; 
matA.pData = new float[matA.rows * matA.cols]{}; 
Matrix &matA_ref = matA; 
Matrix *pMatA = &matA; 
Matrix matB = matA;
pMatA 0xABCDEF00
matB
pData
cols:4
rows:3
```

#### C++ 中的引用
- 引用必须在声明后初始化。  
- 引用与指针：引用更安全。  

```cpp
int &num_ref; // 错误
Matrix &mat_ref; // 错误
```

#### 带有大结构体的函数参数
- 如果大结构体作为函数参数传递。  

```cpp
struct PersonInfo {
    char firstname[256]; 
    char middlename[256]; 
    char lastname[256]; 
    char address[256]; 
    char nationalID[16];
    // 以及更多
};
char *fullname(struct PersonInfo pi) {
    // ...
}
```
- 数据将被复制。这不是一个好的选择！

#### 问题的解决方案
- 一种解决方案是使用指针。  

```cpp
struct PersonInfo {
    char firstname[256]; 
    char middlename[256]; 
    char lastname[256]; 
    char address[256]; 
    char nationalID[16];
    // 以及更多
};
char *fullname(struct PersonInfo *ppi) {
    if (ppi == NULL) {
        cerr << "Invalid pointer" << endl; 
        return NULL;
    } 
    // ...
}
```

#### 作为函数参数的引用
- 引用版本中没有数据复制；效率更高。  
- 对引用的修改会影响原始对象。  

#### 作为函数参数的引用
- 为了避免数据被意外修改，可以使用 `const` 参数。  

```cpp
float matrix_max(const struct Matrix &mat) {
    float max = FLT_MIN; 
    // ...
    return max;
}
```

#### 返回语句
- 如果函数返回类型为 `void`，则 `return;` 语句有效。  
- 只是结束函数的执行，不返回任何值。  

```cpp
void print_gender(bool isMale) {
    if(isMale)
        cout << "Male" << endl;
    else
        cout << "Female" << endl;
    return;
}
```

#### 返回语句
- 返回类型可以是基本类型或复合类型。  
- 按值传递：  
  - 基本类型：常量/变量的值被复制  
  - 指针：地址被复制  
  - 结构体：整个结构体被复制  

```cpp
float maxa = matrix_max(matA);
Matrix *pMat = create_matrix(4,5);
Matrix *create_matrix(size_t rows, size_t cols) {
    Matrix *p = new Matrix{rows, cols}; 
    p->pData = new float[p->rows * p->cols]{1.f, 2.f, 3.f}; 
    // 你应该检查内存是否分配成功  
    // 并且不要忘记释放内存  
    return p;
}
```

#### 如果需要返回大量数据
- 例如矩阵加法函数（A+B->C）  
- 建议的原型：  
  - 使用引用以避免数据复制  
  - 使用 `const` 参数以避免输入数据被修改  
  - 使用非 `const` 引用参数以接收输出  

```cpp
bool matrix_add(const Matrix &matA, const Matrix &matB, Matrix &matC) {
    // 检查三个矩阵的维度  
    // 如果需要，重新创建 matC  
    // 执行：matC = matA + matB  
    // 如果一切顺利，返回 true
}
```

#### OpenCV 中的类似机制
- OpenCV 中的矩阵加法  
[OpenCV 源代码链接](https://github.com/opencv/opencv/blob/master/modules/core/src/arithm.cpp)

#### 内联函数
- 函数调用需要栈操作和跳转。  
- 对于一些频繁调用的小函数，这是一种沉重的代价。  

```cpp
float max_function(float a, float b) {
    if (a > b)
        return a;
    else
        return b;
}
int main() {
    int num1 = 20; 
    int num2 = 30; 
    int maxv = max_function(num1, num2);
    maxv = max_function(numn, maxv);
}
```

#### 内联函数
- 编译器生成的指令可以如下优化以提高效率。  

```cpp
int main() {
    int num1 = 20; 
    int num2 = 30; 
    int maxv =
    maxv =
}
{if (num1 > num2)
    return num1;
else
    return num2;}
{if (numn > maxv)
    return numn;
else
    return maxv;}
```

#### 内联函数
- `inline` 建议编译器进行这种优化。  
- 如果函数过于复杂或存在某些约束，编译器可能不会遵循你的建议。  
- 一些没有 `inline` 的函数可能会被优化为内联函数。  

```cpp
inline float max_function(float a, float b) {
    if (a > b)
        return a;
    else
        return b;
}
```

#### 为什么不用宏？
- 源代码将被预处理器替换。  
- 当然没有函数调用的代价，  
- 并且 `a, b` 可以是任何可比较的类型。  

```cpp
#define MAX_MACRO(a, b) (a)>(b) ? (a) : (b)
```

