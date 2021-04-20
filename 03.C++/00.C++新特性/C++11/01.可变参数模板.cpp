#include <iostream>
using namespace std;

/*

1. 可变参数模板：一个接受可变数目参数的模板函数或模板类。
   参数包：可变数目的参数
   (1). 模板参数包：表示零个或多个模板参数
   (2). 函数参数包：表示零个或多个函数参数
2. 用一个省略号...来指出一个模板参数或函数参数表示一个包

    // Args是一个模板参数包，rset是一个函数参数包
    // Args表示零个或多个模板类型参数
    // rset表示零个或多个函数参数
    template<typename T, typename ... Args>
    void foo(const T &t, const Args& ... rest);
3. sizeof运算符：
    sizeof...(Args):类型参数的数目
    sizeof...(rset):函数参数的数目
4. 定义可变参数模板
    (1). 可变参数模板通常是递归的，第一步调用处理包中的第一个实参，然后用剩余实参调用自身。
    (2). 为了终止递归，还需要定义一个非可变参数的函数
    (3). 非可变参数模板比可变参数模板更特例化，所以在最后一个调用，编译器会选择非可变参数模板。
*/

namespace Test1
{
    // 用于终止递归的非可变参数的函数
    template <typename T>
    void func(T a)
    {
        cout << a << "\tfunc(T a)\n"
             << endl;
    }

    // 可变参数模板
    template <typename T, typename... Args>
    void func(T a, Args... rset)
    {
        cout << "sizeof(Args) = " << sizeof...(Args);
        cout << "  sizeof(rset) = " << sizeof...(rset);
        cout << "  a = " << a << " " << endl;
        func(rset...);
    }
    void test1()
    {
        int a = 10;
        int b = 20;
        char c = 'A';
        double d = 1.99;
        string str = "Chengdu";

        func(a);
        func(a, b);
        func(a, b, c);
        func(a, b, c, d, str);
    }
} // namespace Test1

namespace Test2
{
    template <typename T>
    T add(T a)
    {
        return a;
    }
    template <typename T, typename... Args>
    T add(T a, Args... rset)
    {
        return a + add(rset...);
    }

    void test2()
    {
        cout << add(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << endl;
    }
} // namespace Test2

int main()
{
    Test1::test1();
    Test2::test2();
}