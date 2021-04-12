#include <iostream>
#include <string>
using namespace std;

/*
构造函数

1. 构造函数的初始值列表
(1). 如果类的成员是const、引用，或者属于某种未提供默认构造函数的类类型，我们必须通过
构造函数的初始值列表为这些成员提供初值。
(2). 初始值列表的参数初始化顺序与列表顺序无关，而与类定义时参数定义的顺序有关。
(3). 尽量使用构造函数的初始值列表：
    初始值列表：初始化（效率更快）
    构造函数内部：赋值

*/

namespace Constructor_InitialzationList
{
    class A
    {
    public:
        // 类A没有提供默认构造函数，但提供了带参构造函数
        A(int ia)
        {
            a = ia;
        }

    private:
        int a;
    };

    class B
    {
    public:
        // 类B定义了默认构造函数
        B(int ib = 0) : b(ib)
        {
        }

    private:
        int b;
    };

    class C
    {
    public:
        C(int ic, double id) : x(ic), y(id), a(10)
        {
        }

    private:
        // x是const成员，必须通过构造函数初始值列表赋予初值
        const int x;
        // y是引用类型成员，必须通过构造函数初始值列表赋予初值
        double &y;
        // A没有提供默认构造函数，必须通过构造函数初始值列表赋予初值
        A a;
        // B定义了默认构造函数，可以不必通过初始值列表进行初始化
        B b;
    };
} // namespace Constructor_InitialzationList

/*

2. 委托构造函数

委托构造函数：使用该类中的其他构造函数来完成自己的初始化过程，或者说把自己的一些（或全部）初始化指责
委托给了其他构造函数。

*/

namespace DelegatingConstructor
{
    class A
    {
    public:
        // 非委托构造函数
        A(int ia, string istr) : a(ia), str(istr)
        {
            cout << "Non DelegatingConstructor: " << str << endl;
        }
        // 委托构造函数
        A() : A(10, "C++ 11")
        {
            cout << "DelegatingConstructor 1: " << str << endl;
        }
        A(int ia3) : A(ia3, "")
        {
            cout << "DelegatingConstructor 2: " << str << endl;
        }
        A(string str4) : A(0, str4)
        {
            cout << "DelegatingConstructor 3: " << str << endl;
        }
        A(char ch5) : A(0, "")
        {
            cout << "DelegatingConstructor 4: " << str << endl;
        }
        ~A()
        {

        }

    private:
        int a;
        string str;
    };

    void test()
    {
        A a1(10, "test 1");
        A a2;
        A a3(30);
        A a4("test 4");
        A a5('P');
    }
} // namespace DelegatingConstructor


/*

3. constexpr构造函数

(1). constexpr构造函数：字面值常量类的构造函数可以是constexpr构造函数。constexpr构造函数可以声明为=default的形式或者是删除函数的形式。
(2). constexpr构造函数的函数体一般是空的。
(3). constexpr构造函数必须初始化所有数据成员，初始值或者使用constexpr构造函数，或者是一条常量表达式

*/

class Debug
{
public:
    constexpr Debug(bool b = true):hs(b), io(b), other(b){}
    constexpr Debug(bool h, bool i, bool o):hw(h), io(i), other(0){}

    constexpr bool any()
    {
        return hw || io || other;
    }
    void set_io(bool b){io = b;}
    void set_hw(bool b){hw = b;}
    void set_other(bool b){other = b;}
private:
    bool hw;    // 硬件错误
    bool io;    // IO错误
    bool other; // 其他错误
};

int main()
{
    using namespace DelegatingConstructor;
    test();

    return 0;
}
