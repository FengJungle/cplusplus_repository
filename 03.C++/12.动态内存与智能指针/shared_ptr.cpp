#include <iostream>
using namespace std;

#include <memory>
#include <list>

/*
1. shared_ptr允许多个指针指向同一个对象。

2. shared_ptr支持的操作

    shared_ptr<T> sp;   空智能指针，可以指向类型为T的对象
    p                   将p作为判断条件，如果p指向一个对象，则为true
    *p                  解引用p，获得p指向的对象
    p->mem              等价于(*p).mem
    p.get()             返回p中保存的指针。若智能指针释放了其对象，返回的指针所指向的对象也就消失了
    swap(p,q)           交换p和q中的指针
    p.swap(q)

    make_shared<T>(args) 返回一个shard_ptr，指向一个动态分配的类型为T的对象，使用args初始化此对象
    shared_ptr<T>p(q)    p是shared_ptr q的拷贝，此操作会递增q中的计数器。
    p = q                p和q都是shared_ptr，所保存的指针必须能够相互转换。此操作会递减p的引用计数，递增q的引用计数；
                         若p的引用计数变为0，则将其管理的原内存释放
    p.unique()           若p.use_count()为1，返回true，否则返回false
    p.use_count()        返回与p共享对象的智能指针的数量

*/

void test1()
{
    int num = 10;
    // 下行代码错误：左边是shared_ptr<int>类型，右边是int*类型
    // shared_ptr<int> p1 = &num;

    // p1指针，指向string
    shared_ptr<string> p1;
    // p2指针，指向int的list
    shared_ptr<list<int>> p2;

    shared_ptr<int>pInt = make_shared<int>(10);
    cout << "*pInt = " << *pInt << endl;
    cout << "pInt.unique() = " << pInt.unique() << endl;
    cout << "pInt.count() = " << pInt.use_count() << endl;

    {
        shared_ptr<int> q = pInt;
        cout << pInt.use_count() << endl; // 2
        cout << q.use_count() << endl;    // 2
        cout << q.unique() << endl;       // 0
    }
    // 离开大括号后，引用计数减一

    shared_ptr<int>p3(pInt);
	cout << p3.use_count() << endl;   // 2
	cout << pInt.use_count() << endl; // 2
	cout << pInt.use_count() << endl; // 2
}

void test2()
{
    // 使用shared_ptr的get()方法
    int* p5= nullptr;
    {
        shared_ptr<int> p4 = make_shared<int>(11);
        int *p5 = p4.get();
        cout << "p5 = " << p5 << "\t*p5 = " << *p5 << endl;
    }
    // 离开大括号后，p5所管理的指针已经被智能指针释放了
    cout << "p5 = " << p5 << endl;
}

namespace MyClass
{
    // 自定义的一个类
    class A
    {
    public:
        A(int ia = 0, string istr = "Good") : a(ia), str(istr)
        {
            cout << "Constructor A()" << endl;
        }
        ~A()
        {
            cout << "Destructor ~A()" << endl;
        }
        void show()
        {
            cout << "a = " << a << ", "
                 << " str = " << str.c_str() << endl;
        }

    private:
        int a;
        string str;
    };

    void printSharedPointerInfo(shared_ptr<A> p)
    {
        cout << "use_count = " << p.use_count() << endl;
    }
    void test3()
    {
        shared_ptr<A> p1 = make_shared<A>();
        p1->show();
        shared_ptr<A> p2 = make_shared<A>(10, "Hello World!");
        p2->show();

        auto p3(p1);
        cout << "use_count = " << p1.use_count() << endl;
        cout << "use_count = " << p3.use_count() << endl;

        p1 = p2;
        cout << "use_count = " << p1.use_count() << endl;
        cout << "use_count = " << p2.use_count() << endl;
    }

    // test4: shared_ptr和new结合使用
    void test4()
    {
        // shared_ptr和new结合使用，必须使用直接初始化的形式
        shared_ptr<int>p1(new int(12));
        cout << "*p1 = " << *p1 << endl;
        cout << "p1.use_count() = " << p1.use_count() << endl;

        // 下行代码会报错：必须使用直接初始化的形式
        // shared_ptr<int>p2 = new int(13);

        // 释放p1所指的对象
        p1.reset();
        cout << "p1.use_count() = " << p1.use_count() << endl;
    }

    // test5：使用自己定义的删除器
    void test5()
    {
        // 指向数组的智能指针
        shared_ptr<int> sp_arr(
            new int[10],
            [](int *p) {cout<<"delete []"<<endl;delete []p; });

        // 为数组赋值
        for (int i = 0; i < 10; i++)
        {
            *(sp_arr.get() + i) = i * i;
        }

        // 打印数组元素
        for (int i = 0; i < 10; i++)
        {
            cout << *(sp_arr.get() + i) << "\t";
        }

        // 释放内存,调用自己定义的删除器(lambda表达式)
        sp_arr.reset();
    }
} // namespace MyClass



int main()
{
    // cout << __cplusplus << endl;
    // test1();
    // test2();
    // MyClass::test3();
    // MyClass::test4();
    MyClass::test5();
}