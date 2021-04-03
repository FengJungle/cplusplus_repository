#include <iostream>
#include <cstring>
using namespace std;

/*

原型：void *operator new( size_t, void *p ) throw()  { return p; }

placement new是operator new的一个重载版本。
如果想在已经分配的内存中创建一个对象，使用new是不行的。
也就是说placement new允许你在一个 已经分配好的内存中（栈或堆中） 构造一个新的对象。
原型中void*p实际上就是指向一个已经分配好的内存缓冲区的的首地址。


使用方法如下：

1. 缓冲区提前分配

可以使用堆的空间，也可以使用栈的空间，所以分配方式有如下两种：

class MyClass {…};
char *buf=new char[N*sizeof(MyClass)+ sizeof(int) ] ;

 或者char buf[N*sizeof(MyClass)+ sizeof(int) ];

2. 对象的构造

MyClass * pClass=new(buf) MyClass;

3. 对象的销毁

一旦这个对象使用完毕，必须显式的调用类的析构函数进行销毁对象。但此时内存空间不会被释放，以便其他的对象的构造

pClass->~MyClass();

4. 内存的释放

如果缓冲区在堆中，那么调用delete[] buf;进行内存的释放

如果在栈中，那么在其作用域内有效，跳出作用域，内存自动释放


placement new的好处：

1）在已分配好的内存上进行对象的构建，构建速度快
2）已分配好的内存可以反复利用，有效的避免内存碎片问题

*/

class Rectangular
{
public:
    Rectangular(int ilength = 0, int iwidth = 0) : length(ilength), width(iwidth)
    {
        cout << "Rectangular" << endl;
    }
    ~Rectangular()
    {
        cout << "~Rectangular" << endl;
    }

private:
    int length;
    int width;
};

void test()
{
    cout << "=====================" << endl;
    {
        // 栈空间
        Rectangular arr;

        // placement new
        Rectangular *rec1 = new (&arr) Rectangular(10, 20);
        getchar();

        // 显示调用析构函数
        rec1->~Rectangular();
    }

    cout << "=====================" << endl;
    {
        // 栈空间2
        Rectangular arr2[5];
        // placement new
        Rectangular *rec2 = new (arr2) Rectangular(11, 22);
        getchar();
        // 显示调用析构函数
        rec2->~Rectangular();
    }

    cout << "=====================" << endl;
    {
        // 堆空间
        Rectangular *arr3 = new Rectangular(12, 22);
        memset(arr3, 0, sizeof(Rectangular));
        Rectangular *rec3 = new (arr3) Rectangular(13, 33);
        // 显示调用析构函数
        rec3->~Rectangular();
        // 销毁申请的内存
        delete arr3;
    }
    getchar();
}

int main(int argc, char* argv[])
{

    test();

    return 0;
}