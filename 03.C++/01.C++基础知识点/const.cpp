#include <iostream>
using namespace std;

/*
1. 顶层const与底层const

(1). 顶层const:指针本身是个常量
    Type* const var_name = val;
(2). 底层const:指针所指的对象是一个常量
    const Type var_name = value;
    const Type* var_name = value;
    Type const* var_name = value;
*/
void test1()
{
    // 1. 底层const
    const int a = 10;

    // a是一个底层const，即a是一个常量，不能被修改，所以下面一行代码会报错
    // a = 11; 

    int b = 11;
    const int* pb = &b; 
    // pb是一个底层const，pb是一个指向常量整型（或整型常量）的指针，不允许通过pb修改b的值，下一行代码会报错
    // *pb = 12;

    // 但是pb可以指向别的内容
    pb = NULL;


    // 2. 顶层const
    int c = 13;
    int* const pc = &c;

    // pc是一个顶层const，表示pc本身是一个常量，不允许修改pc的值
    // 下一行代码会报错
    // pc = NULL;

    // 但是可以通过pc修改其指向的内容的值
    *pc = 14;

    // 3. 双重修饰
    int d = 15;
    const int* const pd = &d;

    // pd既是顶层const，也是底层const，既不能通过pd修改d的值，也不能让pd指向别的内容
    
    // 下面代码会报错：pd是顶层const，表示pd本身是一个const，不能指向别的内容
    // pd = &c;

    // 下面代码会报错：pd是底层const，表示pd指向的值是一个常量，不能通过pd修改c的值
    // *pd = 16;
}

/*
2. const_cast<type> (const_var_name)

const_cast可以去掉变量的const属性（只能去掉底层const属性）

*/

void test2()
{
    int a = 10;
    const int *pa = &a;

    // 下面代码会报错：pa是一个底层const，指向一个常量，不能通过pa改变常量对象的值（但pa可以指向别的对象）
    // *pa = 11;

    // 利用const_cast去掉pa的const属性
    int *pa2 = const_cast<int *>(pa);
    *pa2 = 12;
    cout << a << endl;
}

/*
3. 类中的const
(1). const修饰类中的数据成员:const数据成员的初始化只能在类的构造函数的初始化表中进行
    
    const数据成员只在某个对象生存期内是常量，而对于整个类而言却是可变的。
    因为类可以创建多个对象，不同的对象其const数据成员的值可以不同。所以,
    不能在类声明中初始化const数据成员，因为类的对象未被创建时，编译器不
    知道const数据成员的值是什么。
    class A
    {
        const int size = 100;    //错误
        int array[size];         //错误，未知的size
    }
(2). this指针
    普通的成员函数有一个隐式的入口参数，this。this始终指向“这个”，即对象本身，不能改变this的指向，
    因此，this是一个顶层const.

(3). const形参既可以接收const实参，也可以接收非const实参。形参的顶层const会被忽略。

class A{
private:
    int x;
public:
    void func()  // 等同于 void func(A* const this) 
    {
        x = 10;  // 也可以写成 this->x = 10;
    }
}

(3). const修饰类成员函数
    声明：
    class A 
    {
        //......
        void fun() const ; // 等同于 void fun(const A* const this)
    };
    定义： 
    void A::fun() const {……}

a. const函数(fun())可以被const对象调用，但const成员函数中不能调用非const成员函数（因为可能会改变数据成员）;
b. const成员函数可以访问对象的const成员，别的函数不可以；
c. 非const对象可以访问const成员函数；
d. 一个没有被声明为const的成员函数不能被一个const对象调用.
e. 当成员函数的const和non-const版本同时存在，const object只能调用const版本，non-const object只能调用non-const版本。

*/

namespace Test3{
    #include <iostream>
    using namespace std;

    class A{
    public:
        // const数据成员必须通过初始化列表来初始化
        A(int ix = 0, int iy = 0):y(iy){
            x = ix;
        }

        void show(){
            cout << "x = " << x << ", y = " << y << endl;
        }
        
        void set(int ix){
            this->x = ix;
        }

        int get() const{
            // const成员函数，不能修改，下面一行代码会报错
            // x = 12;

            // const成员函数不能调用非const成员函数
            // this->set(12);

            return x;
        }

        // const成员函数可以访问const数据成员、普通成员、const成员函数
        int add() const{
            // const 成员函数不能调用非const成员函数
            // show();
            return x + y + get() + 12;
        }

    private:
        int x;
        const int y;
    };

    void test3()
    {
        A a1(10,20);
        a1.show();
        a1.set(11);
        cout << a1.add() << endl;

        const A a2(30, 40);
        // const类对象的每一个成员都是const成员
        // a2.set(31);
    }
}

int main()
{
    // test1();

    // test2();

    Test3::test3();

    return 0;
}