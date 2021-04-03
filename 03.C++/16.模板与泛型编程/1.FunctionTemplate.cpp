#include <iostream>
using namespace std;

/*

1. 函数模板：模板类型参数 typename或class

*/

namespace FuncTemplate1
{
    template <typename T>
    T getMax(T a, T b)
    {
        return a > b ? a : b; // 前提是类型T必须定义了>运算符
    }

    void test1()
    {
        cout << getMax(10, 20) << endl;     // int
        cout << getMax(1.12, 2.34) << endl; // double
        cout << getMax('C', 'M') << endl;   // char
    }
} // namespace FuncTemplate1

/*

2. 函数模板：非类型模板参数

* 用typename(class)来修饰的模板参数都是类型模板参数 


* 模板除了定义类型参数，还可以在模板定义非类型参数。
* 非类型形参：表示一个固定类型的常量而不是一个类型。
* 固定类型是有局限的，只有整形，指针和引用才能作为非类型形参，
* 而且绑定到该形参的实参必须是常量表达式，即编译期就能确认结果。

* 非类型形参的局限:
* 1.浮点数不可以作为非类型形参，包括float，double
* 2.类不可以作为非类型形参。
* 3.字符串不可以作为非类型形参
* 4.整形，可转化为整形的类型都可以作为形参，比如int，char，long，unsigned，bool，short（enum声明的内部数据可以作为实参传递给int，但是一般不能当形参）
* 5.指向对象或函数的指针与引用（左值引用）可以作为形参
 
* 非类型实参的局限:
* 1.实参必须是编译时常量表达式，不能使用非const的局部变量，局部对象地址及动态对象
* 2.非Const的全局指针，全局对象，全局变量都不是常量表达式。
* 3.由于形参的已经做了限定，字符串，浮点型即使是常量表达式也不可以作为非类型实参
* 备注：常量表达式基本上是字面值以及const修饰的变量
*/

namespace FuncTemplate2
{
    template <int times>
    void print()
    {
        cout << times << endl;
    }

    // 全局const
    const int num1 = 10;
    // static (非const)
    static int num2 = 11;
    // 全局(非const)
    int num3 = 12;

    void test2()
    {
        print<num1>(); // Right
        //print<num2>(); // Wrong
        //print<num3>(); // Wrong

        // const局部变量
        const int num4 = 13;
        print<num4>(); // Right

        // 非const局部变量
        int num5 = 14;
        //print<num5>(); // Wrong

        // 常量
        print<5>(); // Right
        print<3 + 4>();
        print<((1 + 3) > 3)>();
        //print<(num5 > 10)>(); // Wrong
    }
} // namespace FuncTemplate2

/*
 3. 默认模板实参
*/

namespace FuncTemplate3
{
    template<typename T, typename U = char>
    void tempFunc(T t, U u)
    {
        cout << t << ":" << u << endl;
    }

    template<typename T = int, typename U = string>
    void tempFunc2()
    {
        cout << "template::tempFunc2" << endl;
    }

    void tempFunc2()
    {
        cout << "tempFunc2" << endl;
    }

    void test3()
    {
        // 指定模板类型
        tempFunc<int,int>(10,20);
        // 第二个类型为默认模板实参char
        tempFunc<long>(11,'A');

        // 调用普通函数
        tempFunc2();

        // 调用模板函数
        tempFunc2<short,string>();
        tempFunc2<bool>();

        // 空的尖括号<>表示调用默认类型的模板函数
        tempFunc2<>();
    }
}

namespace FuncTemplate4
{
    // 普通函数
    int myFunc(int tv1, int tv2)
    {
        return tv1 + tv2;
    }

    // 定义函数指针类型pfunc
    typedef int (*FuncType)(int, int);

    // 第二个模板参数为默认类型
    template <typename T, typename F = FuncType>
    void testFunc(T i, T j, F func = myFunc)
    {
        cout << myFunc(i, j) << endl;
    }

    void test4()
    {
        testFunc(15, 16);
    }
} // namespace FuncTemplate4

int main()
{
    // FuncTemplate1::test1();
    // FuncTemplate2::test2();
    FuncTemplate3::test3();
    FuncTemplate4::test4();
    return 0;
}