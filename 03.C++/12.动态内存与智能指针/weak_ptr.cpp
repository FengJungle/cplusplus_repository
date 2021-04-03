#include <iostream>
using namespace std;

#include <memory>

/*
1. weak_ptr
(1). 是一种不控制所指向对象生存期的智能指针，它指向由一个shared_ptr管理的对象。
(2). 将一个weak_ptr绑定到一个shared_ptr不会改变shared_ptr的引用计数。
(3). 一旦最后一个指向对象的shared_ptr被销毁，对象就会被释放。（即使有weak_ptr指向对象，对象也还是会被释放）。

2. weak_ptr支持的操作

    weak_ptr<T> w      空weak_ptr，可以指向类型为T的对象
    weak_ptr<T> w(sp)  与shared_ptr sp指向相同对象的weak_ptr

    w = p              p可以是一个shared_ptr或一个weak_ptr，赋值后w与p共享对象

    w.reset()          将w置为空

    w.use_count()      与w共享对象的shared_ptr的数量

    w.expired()        若w.use_count()为0，返回true，否则返回false

    w.lock()           如果expired为true，返回一个空shared_ptr；否则返回一个指向w对象的shared_ptr

*/

void test1()
{
    // 创建一个weak_ptr时，要用一个shared_ptr来初始化它
    shared_ptr<int> sp_int = make_shared<int>(10);
    weak_ptr<int> w_int(sp_int);
    cout << *sp_int << endl;           // 10
    cout << w_int.use_count() << endl; // 1

    // 由于对象可能不存在，不能使用weak_ptr直接访问对象
    // 必须调用lock()：检查weak_ptr指向的对象是否仍旧存在，如果存在，lock()返回指向共享对象的shared_ptr。
    shared_ptr<int> tmp = w_int.lock();
    if (tmp) // 如果共享对象存在
    {
        cout << " shared object exist" << endl;
        cout << *tmp << endl;
    }

    cout << w_int.use_count() << endl; // 0
    shared_ptr<int> tmp2 = w_int.lock();
    if (tmp) // 如果共享对象存在
    {
        cout << " shared object exist" << endl;
        cout << *tmp << endl;
    }
    else
    {
        cout << " shared object not exist" << endl;
    }
}

int main()
{
    test1();

    return 0;
}