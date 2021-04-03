#include <iostream>
using namespace std;

/*

一. 拷贝构造函数
(1). 如果没有为一个类定义拷贝构造函数，编译器会定义一个，即合成拷贝构造函数，编译器从给定对象中依次将每个非static成员拷贝到正在创建的对象中。
(2). 成员类型决定其如何拷贝：
     a. 类类型成员：使用其拷贝构造函数来拷贝；
     b. 内置类型成员：直接拷贝；
     c. 逐个元素拷贝数组类型成员，如果数组元素是类类型，则用其拷贝构造函数进行拷贝；

2. 直接初始化 与 拷贝初始化
    a. 直接初始化：要求编译器使用普通的函数匹配来选择与我们提供的参数最匹配的构造函数；
    b. 拷贝初始化：要求编译器将右侧运算对象拷贝到正在创建的对象中，如果需要的话还要进行类型转换

3. 拷贝初始化在以下情况发生：
    a. 用=定义变量；
    b. 将一个对象作为实参传递给一个 非引用 类型的形参；
    c. 从一个返回类型为 非引用 类型的函数返回一个对象；
    d. 用花括号列表初始化一个数组中的元素或一个聚合类中的成员；

注意：拷贝构造函数被用来初始化 非引用 类类型参数，这一特性解释了“拷贝构造函数自己的参数必须是引用类型”，
     如果拷贝构造函数的参数不是引用类型，那么拷贝构造函数会无限循环调用下去，永远不会成功和结束。

二. 拷贝赋值运算符

如果类未自己定义拷贝赋值运算符，编译器将合成一个拷贝赋值运算符。

*/

namespace Namespace1
{
    // 定义类A
    class A
    {
    public:
        A(int inum = 0, string istr = "") : num(inum), str(istr)
        {
            cout << "A::Default Constructor";
            show();
        }
        // 拷贝构造函数
        A(const A &a)
        {
            cout << "A::Copy Constructor";
            this->num = a.num;
            this->str = a.str;
            show();
        }
        // 拷贝赋值 运算符
        A& operator=(const A& a)
        {
            cout<<"A::Copy Assignment";
            this->num = a.num;
            this->str = a.str;
            show();
        }
        void show()
        {
            cout << "\t" << num << "\t" << str << endl;
        }

    private:
        int num;
        string str;
    };

    // 将一个对象作为实参传递给一个 非引用 类型的形参，调用拷贝构造函数
    void testFunc(A a)
    {

    }
    // 从一个返回类型为 非引用 类型的函数返回一个对象，调用拷贝构造函数
    A testFunc2()
    {
        A *a2 = new A(11, "shenzhen");
        return *a2;
    }

    void test1()
    {
       A* a1= new A(10,"chengdu");
       testFunc(*a1);
       testFunc2();

       A a4(12, "Beijing");
       a4 = *a1; // 拷贝赋值运算符
    }
} // namespace Namespace1

/*

三. 使用=default

1. 通过将拷贝控制成员定义为=default来显示要求编译器生成合成的版本
2. 我们只能对 具有合成版本的成员函数 使用=default，即默认构造函数或拷贝控制成员

*/

namespace Namespace2
{
    class B
    {
    public:
        // 使用合成版本的构造函数
        B() = default;

        // 使用合成版本的拷贝构造函数
        B(const B &ib) = default;

        B &operator=(const B &ib);

        // 使用合成版本的析构函数
        ~B() = default;

        void show()
        {
            cout << "\t" << num << "\t" << str << endl;
        }

    private:
        int num;
        string str;
    };
    // 使用合成版本的拷贝赋值
    B &B::operator=(const B &ib) = default;

    void test2()
    {
    }
} // namespace Namespace2

/*

三. 使用=delete

1. 在函数的参数列表后面加上=delete来指出我们希望将它定义为删除的函数
2. 删除的函数：我们虽然声明了它们， 但不能以任何方式使用它们

3. 不能删除析构函数，否则编译器不允许定义该类型变量或创建该类的临时对象
   如果为类定义了删除析构函数，虽然我们不能定义这种类型的变量或成员，但是可以动态分配这种类型的对象，但是无法释放这些对象

*/

namespace Namespace3
{

    class C
    {
    public:
        // 使用合成版本的默认构造函数
        C() = default;

        // 将拷贝构造函数定义为删除的函数：不能拷贝构造
        C(const C &ic) = delete;

        // 将拷贝赋值运算符定义为删除的函数：不能拷贝赋值
        C &operator=(const C &ic) = delete;

        // 使用合成版本的析构函数
        ~C() = default;

        void set(int inum,string istr)
        {
            this->num = inum;
            this->str = istr;
        }

        void show()
        {
            cout << "\t" << num << "\t" << str << endl;
        }

    private:
        int num;
        string str;
    };

    void testFunc(C c3)
    {

    }

    void test3()
    {
        // 使用默认构造函数
        C* c = new C;
        c->set(10,"Shanghai");
        c->show();

        // Wrong: 不能拷贝构造
        // testFunc(*c);

        // Wrong, 不能拷贝赋值
        C c2;
        // c2 = *c;

    }
} // namespace Namespace3

int main()
{
    Namespace1::test1();

    return 0;
}