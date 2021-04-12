# 1. 常量表达式

常量表达式是指值不会改变并且在编译过程就能得到计算结果的表达式。字面值属于常量表达式，用常量表达式初始化的const对象也是常量表达式。
一个对象或表达式是不是常量表达式由它的数据类型和初始值共同决定

```
const int max_file = 290;   // max_file是常量表达式
const int limit = max_file; // limit是常量表达式
int another = 12；          // 尽管12是字面值常量，但数据类型只是普通int而不是const int，所以another不是常量表达式
const int size = getSize(); // 尽管size本身是常量，但getSize()在编译器不能获得，所以size不是常量表达式
```

# 2. constexpr变量
C++11新标准规定，允许将变量声明为constexpr类型，以便由编译器来验证变量的值是否是一个常量表达式。  
声明为constexpr的变量一定是一个常量，而且必须使用常量表达式初始化：

```
constexpr int mf = 20;      // 20是常量表达式
constexpr int limit = mf+1; // mf+1是常量表达式
constexpr int sz = size();  // 只有当size()是一个constexpr函数时，才是一条正确的声明语句
```

# 3. constexpr修饰函数
C++11中的constexpr指定的**函数返回值和参数**必须要保证是字面值，而且**必须有且只有一行return代码**，这给函数的设计者带来了更多的限制，比如通常只能通过return 三目运算符+递归来计算返回的字面值。 
而C++14中只要保证返回值和参数是字面值就行了，函数体中可以加入更多的语句，方便了更灵活的计算。   

**注意：**
* 1. 执行初始化任务时，编译器把constexpr函数的调用替换成其结果值。为了能够在编译过程中随时展开，**constepxr函数被隐式地指定为内联函数**。
* 2. 内联函数和constexpr函数可以在程序中多次定义。但是，对于给定的内联函数或constexpr函数，它的多个定义必须完全一致。基于这个原因，内联函数和constexpr函数通常定义在**头文件**中。

```
int get_e()
{
    return 12;
}

constexpr int get_f()
{
    return 10;
}

constexpr int get_g()
{
    int a; // 错误！
    return 14;
}

constexpr int get_h(int a)
{
    return 1+a;
}

int main(int argc, char* argv[])
{
    constexpr int a = 10;          // a是一个常量表达式
    constexpr int c = a + 12;      // a+12是一个常量表达式
    const int b = 11;              // b是一个常量
    constexpr int d = b;           // d是一个常量表达式
    // constexpr int e = get_e();  // get_e()不是一个constexpr函数，所以该语句错误
    constexpr int f = get_f();     // get_f()是一个constexpr函数，所以该语句正确
    constexpr int g = get_g();     // 尽管声明get_g()是一个constexpr函数，但函数内只允许有return语句
    constexpr int h = get_h(2);    // get_h(int a)是一个constexpr函数，且参数和返回值是字面值常量，函数内只有return语句
}
```

# 4. const和constexpr的比较
* constexpr修饰指针时，与const修饰指针差异甚大！**constexpr将它定义的对象置为了顶层const**
```
// p是一个指向常量的指针，即p是一个底层const
const int *p = nullptr;

// q是一个指向整数的常量值真，即q是一个顶层const
constexpr int *q = nullptr;
```

* const并不能代表“常量”，它仅仅是对变量的一个修饰，告诉编译器这个变量只能被初始化，且不能被直接修改（实际上可以通过堆栈溢出等方式修改）。而这个变量的值，**可以在运行时也可以在编译时指定**。

* constexpr可以用来修饰变量、函数、**构造函数**。一旦以上任何元素被constexpr修饰，那么等于说是告诉编译器 “请大胆地将我看成编译时就能得出常量值的表达式去优化我”  --> 给编译器足够的信心在编译期去做被constexpr修饰的表达式的优化  


比如：
```
const int get_h()
{
    return 10;
}
constexpr int get_i()
{
    return 23;
}

int main(int argc, char* argv[])
{
    // 该行代码编译报错，对于get_h() ，胆小的编译器并没有足够的胆量去做编译期优化，哪怕函数体就一句return 字面值;
    int arr1[get_h()];  

    // 编译通过，编译期大胆地将get_i()做了优化，在编译期就确定了get_i计算出的值10而无需等到运行时再去计算
    int arr2[get_i()];
}
```