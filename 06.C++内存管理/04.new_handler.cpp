/*
*
* 当operator new没有能力为你分配出你所申请的memory，会
* 抛出一个std::bad_alloc exception. 某些老的编译器则是返回0，
* 我们可以通过new (nothrow) Foo命令编译器那么做
* 
* 抛出exception之前，会先（不止一次）调用一个可由client指定的handler
*  typedef void(*new_handler)();
*  new_handler set_new_handler(new_handler p) throw();
* 
*  设计良好的new handler会有两种做法：
*  1. 释放一些暂时不适用的memory，让更多的memory可用
*  2. 调用abort()或exit()
*/


#include <iostream>
#include <assert.h>
using namespace std;


/*
*
* Demo: 注意返回值为void, 没有函数参数
*
*/
void no_more_memory()
{
    cout<<"out of memory"<<endl;
    abort();
}

int main(int argc, char* argv[])
{
    set_new_handler(no_more_memory);

    int* p = new int[10000000000];
    assert(p);


    return 0;
}