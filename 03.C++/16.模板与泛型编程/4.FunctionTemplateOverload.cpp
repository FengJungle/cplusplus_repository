#include <iostream>
using namespace std;


/*

1. 函数模板重载

(1). 重载：函数（函数模板）名字相同，参数数量或者参数类型不同
(2). 可以重载普通非模板函数
(3). 当普通函数和模板函数都匹配时，编译器会选择普通函数

*/

namespace Namespace1
{
    template <typename T>
    void myFunc(T tv)
    {
        cout << "myFunc(T tv)" << endl;
    }

    // 重载myFunc，函数模板，参数类型不同
    template <typename T>
    void myFunc(T *tv)
    {
        cout << "myFunc(T* tv)" << endl;
    }

    // 重载myFunc,普通非模板函数
    void myFunc(int tv){
        cout << "myFunc(int tv)" << endl;
    }

    void test()
    {
        char a = 10;
        int *b = nullptr;
        myFunc(a);  // myFunc(T tv)
        myFunc(b);  // myFunc(T *tv)
        myFunc(14); // myFunc(int tv)
    }
} // namespace Namespace1

int main()
{
    Namespace1::test();

    return 0;
}