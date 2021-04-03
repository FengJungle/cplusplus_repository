#include <iostream>
using namespace std;

/*

static_cast<new_type>      (expression)
dynamic_cast<new_type>     (expression) 
const_cast<new_type>       (expression) 
reinterpret_cast<new_type> (expression)

*/

/*

1. static_cast

static_cast相当于C语言中的强制转换，该运算符把expression转换成new_type类型，用来强迫隐式转换，
例如non-const对象转为const对象，编译时检查，用于非多态的转换，可以转换指针及其他，但没有运行时
类型检查来保证转换的安全性。它主要有如下几种用法：

(1). 用于类层次结构中基类（父类）和派生类（子类）之间指针或引用的转换。
    a. 进行上行转换（把派生类的指针或引用转换成基类表示）是安全的；
    b. 进行下行转换（把基类指针或引用转换成派生类表示）时，由于没有动态类型检查，所以是不安全的。
(2). 用于基本数据类型之间的转换，如把int转换成char，把int转换成enum。这种转换的安全性也要开发人员来保证。
(3). 把空指针转换成目标类型的空指针。
(4). 把任何类型的表达式转换成void类型。

注意：static_cast不能转换掉expression的const、volatile、或者__unaligned属性。

*/

void test1()
{
    // 将char强制转换为int
    char ch = 'A';
    int a = static_cast<int>(ch);
    cout << "ch = " << ch << "\ta = " << a << endl;

    // 将double强制转换为int
    double f = 9.92;
    int b = static_cast<int>(f);
    cout << "f = " << f << "\tb = " << b << endl;

    // Wrong, static_cast不能去掉const属性
    const float pi = 3.1415;
    //float pi = static_cast<float>(pi);
}

/*

2. dynamic_cast

dynamic_cast<type*>(e)
dynamic_cast<type&>(e)
dynamic_cast<type&&>(e)

type必须是一个类类型，并且通常情况下该类型含有虚函数
在第一种形式中，type必须是一个有效的指针;
在第二种形式中，type必须是一个左值;
在第三种形式中，type必须是一个右值。

在上面所有形式中，e的类型必须符合以下三个条件中的任何一个：
(1). e的类型是是目标类型type的公有派生类
(2). e的类型是目标type的共有基类
(3). e的类型就是目标type的的类型

如果一条dynamic_cast语句的转换目标是指针类型并且失败了，则结果为0。
如果转换目标是引用类型并且失败了，则dynamic_cast运算符将抛出一个std::bad_cast异常(该异常定义在typeinfo标准库头文件中)。
e也可以是一个空指针，结果是所需类型的空指针。

dynamic_cast主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换（cross cast）。

*/

class A
{
public:
    virtual void show()
    {
        cout << "A" << endl;
    }
};
class B : public A
{
public:
    virtual void show()
    {
        cout << "B" << endl;
    }
};

void test2()
{
    A *a = new A();
    B *b = new B();
    // 向上转型
    if (A *c = dynamic_cast<A *>(b))
    {
        c->show();
        cout << "dynamic_cast success" << endl;
    }
    else
    {
        c->show();
        cout << "dynamic_cast fail" << endl;
    }

    // 向下转型,dynamic_cast具有类型检查的功能，比static_cast更安全
    B* b2 = dynamic_cast<B*>(a);   
}

/*

3. const_cast

const_cast，用于修改类型的const或volatile属性。 

该运算符用来修改类型的const(唯一有此能力的C++-style转型操作符)或volatile属性。
除了const 或volatile修饰之外， new_type和expression的类型是一样的。
(1). 常量指针被转化成非常量的指针，并且仍然指向原来的对象；
(2). 常量引用被转换成非常量的引用，并且仍然指向原来的对象；
(3). const_cast一般用于修改底层const。如const char *p形式。

*/

void test3()
{
    const int a = 10;
    int b = a;
    b = 11;
    // a = 12;            // Wrong, a不能被修改

    const char* ch = "Good";
    // char* ch2 = ch;    // Wrong
    char* ch3 = const_cast<char*>(ch);
}

/*

4. reinterpret_cast

new_type必须是一个指针、引用、算术类型、函数指针或者成员指针。
转换后的类型与源类型有相同的比特位。
它可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针（先把一个指针转换成一个整数，再把该整数转换成原类型的指针，还可以得到原先的指针值）。

reinterpret_cast意图执行低级转型，实际动作（及结果）可能取决于编辑器，这也就表示它不可移植。

*/

// Returns a hash code based on an address
// unsigned short Hash(void *p)
{
    unsigned int val = reinterpret_cast<unsigned int>(p);
    return (unsigned short)(val ^ (val >> 16));
}

void test4()
{
    int a[20];
    for (int i = 0; i < 20; i++)
        cout << Hash(a + i) << endl;
}

int main()
{

    // test1();
    test2();
    // test3();
    // test4();

    return 0;
}