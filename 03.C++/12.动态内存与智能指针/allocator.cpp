#include <iostream>
using namespace std;

#include <memory>

/*
1. allocator类提供一种类型感知的内存分配方法，分配的内存是原始的，未构造的。

2. 标准库allocator类及其算法

    allocator<T> a      定义一个名为a的allocator对象，它可以未类型为T的对象分配内存

    a.allocate(n)       分配一段原始的、未构造的内存，保存为n个类型为T的对象

    a.deallocate(p,n)   释放从T*指针p中开始的内存，这块内存保存了n个类型为T的对象；
                        p必须是一个先前由allocate返回的指针，且n必须是p创建时所要求
                        的大小。在调用deallocate之前，必须先对每个在这块内存中创建
                        的对象调用destroy

    a.construct(p,args) p必须是一个类型为T*的指针，指向一块原始内存；
                        arg被传递给类型为T的构造函数，用来在p指向的内存中构造一个对象

    a.destroy(p)        p为类型为T*类型的指针，此算法对p指向的对象执行析构函数

*/

namespace Allocator_Test1
{
    // 自定义的一个类
    class Demo
    {
    public:
        Demo(int ix = 0, string istr = "Good") : x(ix), str(istr)
        {
            cout << "Constructor Demo()\t";
            show();
        }
        ~Demo()
        {
            cout << "Destructor ~Demo()\t";
            show();
        }
        void show()
        {
            cout << "x = " << x << ", "
                 << " str = " << str.c_str() << endl;
        }

    private:
        int x;
        string str;
    };

    void test1()
    {
        // 可以分配 Demo 的allocator对象
        allocator<Demo> alloc;
        // 分配4个未初始化的Demo
        auto const p = alloc.allocate(4);

        // q 指向最后构造的元素之后的位置
        auto q = p;
        alloc.construct(q++, Demo(9, "Beijing"));
        alloc.construct(q++, Demo(10, "Chengdu"));
        alloc.construct(q++, Demo(11, "Shenzhen"));
        alloc.construct(q++, Demo(12, "Hangzhou"));
    }
}

int main()
{
    Allocator_Test1::test1();

    return 0;
}