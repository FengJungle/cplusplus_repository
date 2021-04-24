#include <iostream>
using namespace std;


/*

1. 模板实参推断

(1). const转换：可以将一个非const对象的引用或指针传递给一个const的引用或指针形参；
(2). 数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。
     一个数组实参可以转换为一个指向其首元素的指针；
     一个函数实参可以转换为一个该函数类型的指针。
(3). 以下类型转换不能应用于函数模板：
    a. 算数转换：运算符的运算对象会转换为最宽的数据类型（short->int等）；
    b. 派生类向基类的转换；
    c. 用户定义的转换：如operator type() const, 隐式类类型转换（默认构造函数）

2. 函数模板显示实参

某些情况下，编译器无法推断出模板实参类型。有时我们希望允许用户控制模板实例化。
(1). 指定显示模板实参：在函数名之后，实参列表之前的尖括号<>中指定实参类型
     
    auto funcName<指定类型，如int>(实参列表);

(2). auto推断函数模板返回类型
(3). auto与decltype结合，尾置返回类型推断函数模板返回类型
     auto templateFun(T tv1, U tv2) -> decltype(tv1+tv2)

*/

namespace Test1
{
    template <typename T>
    T funcObj(T a, T b)
    {
        cout << "funcObj" << endl;
    }
    template <typename T>
    T funcRef(const T &a, const T &b)
    {
        cout << "funcRef" << endl;
    }
    void testFunc()
    {
        // 普通int
        int a = 10;
        // 顶层const int
        const int b = 11;

        funcObj(a, b); // Right
        funcRef(a, b); // Right

        double arr1[5], arr2[6];
        funcObj(arr1, arr2); // Right, 数组名转换为指向数组首元素的指针，即funcObj(double*, double*)
        // 形参是const T&，即const引用
        // 实参1类型是：double[5]
        // 实参2类型是：double[6]
        // funcRef(arr1, arr2); // Wrong
    }

    // 定义类A
    class A
    {
    public:
        A(){};

        // 定义转换函数，转换为一个int
        operator int() const
        {
            return 10;
        }
    };
    //派生类B
    class B : public A
    {
    };
    template <typename T>
    void funcClass(T a, T b)
    {
        cout << "funcClass" << endl;
    }
    void testClass()
    {
        A a;
        B b;

        // 测试转换函数
        int num = 10 + a; // 类A的对象a转换为int
        cout << num << endl;

        funcClass(10, num); // T为int
        // funcClass(num, a);  // Wrong, 类A的对象a不能转换为int
    }

    void test3()
    {
        int x = 10;
        short y = 11;
        // funcClass(x,y);// Wrong, y不能自动转换为int

        // Right, <>中指定模板实参类型为int
        funcClass<int>(x, y);
        // Right, <>中指定模板实参类型为char
        funcClass<char>(x, y);
    }
} // namespace Test1

int main()
{

    return 0;
}