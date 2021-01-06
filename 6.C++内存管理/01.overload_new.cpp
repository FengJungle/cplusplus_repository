#include <iostream>
using namespace std;

/*
*
* 类的成员函数，重载operator new和operator delete
* 如果编译器发现类重载了Operator new([])和operator delete([]),编译器会首先调用重载版本
*
*/
class Bad
{
};
class Simple
{
public:
    Simple()
    {
        cout << "Simple::Default Constructor()" << endl;
    }
    Simple(int inum) : num(inum), ch(nullptr)
    {
        cout << "Simple::Constructor()" << endl;
        throw Bad();
    }
    ~Simple()
    {
        cout << "Simple::Destructor()" << endl;
    }
    /************************************/
    // 重载以下4个函数，注意是static
    static void *operator new(size_t size)
    {
        cout << "Simple::operator new" << endl;
        Simple *p = (Simple *)malloc(size);
        return p;
    }
    static void *operator new[](size_t size)
    {
        cout << "Simple::operator new[]" << endl;
        Simple *p = (Simple *)malloc(size);
        return p;
    }
    static void operator delete(void *p)
    {
        cout << "Simple::operator delete" << endl;
        return delete (p);
    }
    static void operator delete[](void *p)
    {
        cout << "Simple::operator delete[]" << endl;
        return delete (p);
    }
    /************************************/
    // 标准库提供的placement new的重载
    // 只是传回start，不分配内存
    static void *operator new(size_t size, void *start)
    {
        cout << "operator new(size_t size, void* start)" << endl;
        return start;
    }
    static void operator delete(void *, void *)
    {
        cout << "operator delete(void*, void*)" << endl;
    }
    // 重载的placement new，参数列不同，但第一个参数类型必须是size_t
    static void *operator new(size_t size, long extra)
    {
        cout << "operator new(size_t size, long extra)" << endl;
        return malloc(size + extra);
    }
    static void operator delete(void *, long)
    {
        cout << "operator delete(void*, long)" << endl;
    }
    // 重载的placement new，参数列不同，但第一个参数类型必须是size_t
    static void *operator new(size_t size, long extra, char init)
    {
        cout << "operator new(size_t size, long extra, char init)" << endl;
        return malloc(size + extra);
    }
    static void operator delete(void *, long, char)
    {
        cout << "operator delete(void*, long, char)" << endl;
    }
    // 下列重载编译器会报错：第一参数类型必须是size_t
    /*
    void* operator new(long extra, char init)
    {
        return malloc(extra);
    }*/

private:
    char *ch;
    int num;
};

void test_overloaded_member_new()
{
    cout << "member new...\n";
    Simple *p = new Simple(5);
    delete p;

    cout << "member new[]...\n";
    Simple *p2 = new Simple[3];
    delete[] p2;

    // 使用 :: 调用global new/global delete
    cout << "global new...\n";
    Simple *p3 = ::new Simple(3);
    ::delete (p3);

    cout << "global new[]...\n";
    Simple *p4 = ::new Simple[10];
    ::delete (p4);
}

void test_global_new()
{
    int *arr = ::new int[10];
    ::delete[] arr;
}

/*
*
* 1. 每一个版本必须有独特的参数列，且第一个参数类型必须是size_t
* 2. 每一个重载版本的placement new， 编译器并不强求实现出对应版本的delelte
* 3. 只有在抛出异常的时候，才会调用用户定义的delete，如果没有定义delete，编译器视为放弃处理异常
*/
void test_overloaded_placement_new()
{
    int start = 0;
    cout << "p1\t";
    Simple *p1 = new Simple;
    cout << "p2\t";
    Simple *p2 = new (&start) Simple;
    cout << "p3\t";
    Simple *p3 = new (100) Simple;
    cout << "p4\t";
    Simple *p4 = new (100, 'a') Simple;
    cout << "p5\t";
    Simple *p5 = new (100) Simple(1);
    cout << "p6\t";
    Simple *p6 = new (100, 'a') Simple(1);
    cout << "p7\t";
    Simple *p7 = new (&start) Simple(1);
    cout << "p8\t";
    Simple *p8 = new Simple(1);
}

int main(int argc, char *argv[])
{
    // test_overloaded_member_new();

    // test_global_new；

    test_overloaded_placement_new();

    return 0;
}