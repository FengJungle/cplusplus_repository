#include <iostream>
using namespace std;

#include <memory>

/*

1. unique_ptr

一个unique_ptr拥有它所指向的对象：某个时刻，只能有一个unique_ptr指向一个给定对象
当unique_ptr被销毁时，它所指向的对象也被销毁。

一个unique_ptr拥有它所指向的对象，所以unique_ptr不支持普通的拷贝或赋值。
但可以拷贝或者赋值一个将要被销毁的unique_ptr，比如给函数传递一个unique_ptr和从函数返回一个unique_ptr。

2. unique_ptr

    unique_ptr<T> p;       空unique_ptr,可以指向类型为T的对象。p会使用delete来释放它的指针
    unique_ptr<T,D> p2;    空unique_ptr,可以指向类型为T的对象。p2会使用一个类型为D的可调用对象来释放它的指针
    unique_ptr<T,D> p3(d); 空unique_ptr,可以指向类型为T的对象。p3会使用一个类型为D的对象d来释放它的指针

    u = nullptr            释放u指向的对象，将u置为空
    u.release()            u放弃对指针的控制权，返回指针，并将u置为空
    u.reset()              释放u指向的对象
    u.reset(q)             如果提供了内置指针q，令u指向这个对象，否则将u置为空
    u.reset(nullptr)       
*/

namespace U_MyClass
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
    void test1()
    {
        unique_ptr<int> up1(new int(10));

        // 下面两行代码会报错：unique_ptr不支持普通的拷贝或赋值
        // auto p2 = up1;
        // auto p3(up1);

        unique_ptr<A> up2(new A(10, "Chengdu")); // Call constructor
        A* up3 = up2.release();                // release()方法使up2放弃对其指向对象的控制权，返回对象的指针
        up3->show();
        delete up3;

        unique_ptr<A>up4(new A(11,"Beijing"));// Call constructor
        up4.reset();                          // Call destructor

        unique_ptr<A> up5(new A(12, "Shenzhen")); // Call constructor
        unique_ptr<A> up6(new A(13, "Guangzhou"));// Call constructor
        up6.reset(up5.release());
        A* p7 = up6.release();
        p7->show();               // a = 12,  str = Shenzhen
    }
} // namespace U_MyClass


int main()
{
    U_MyClass::test1();

    return 0;
}