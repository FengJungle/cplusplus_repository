#include <iostream>
using namespace std;

/*

1. 泛化：常规的，大众的

2. 特化：往往代表着从泛化版本中抽出来的一组子集

(1). 全特化：把泛化版本的所有模板参数都用具体的类型来代替构成一个全特化版本
     
     a. 全特化实际上等价于实例化一个函数模板，但并不是一个函数重载

     b. 编译器考虑的顺序：优先选择普通函数 --> 特化版本 --> 泛化版本

(2). 偏特化（局部特化）：
     a. 模板参数数量上的偏特化：比如针对func函数模板，第一个模板参数类型为double，第二个模板参数不特化
        实际上，从模板参数数量上来讲，函数模板不能偏特化，否则会导致编译错误
     b. 模板参数范围上的偏特化：int -> const int, 类型变小；T -> T*, T -> T&, T-> T&&
        实际上对于函数模板来讲，也不存在模板参数范围上的偏特化。因为这种所谓模板参数范围上的偏特化，实际上是函数模板的重载。
     c. 通过重载实现偏特化
*/

namespace Namespace1
{
    // 泛化
    template <typename T, typename U>
    void func(T &tv1, U &tv2)
    {
        cout << "func Generalization version\t";
        cout << tv1 << "   " << tv2 << endl;
    }

    // 全特化
    template<> // 全特化<>里面为空
    void func<int, double>(int& tv1, double& tv2) // <int, double>可以省略，因为根据实参可以完全推导出T和U类型
    {
        cout << "func Specialization version\t";
        cout << tv1 << "   " << tv2 << endl;
    }

    // 普通函数：重载
    void func(int tv1, double tv2)
    {
        cout << "func overload version\t";
        cout << tv1 << "   " << tv2 << endl;
    }

    // 偏特化：数量偏特化 --> 不能偏特化
    /*template<typename T>
    void func<double ,U><double& tv1, U& tv2)
    {
        // ....
    }*/
    

    void test1()
    {
        const char *ch = "I love China";
        int i = 12;
        // 实例化void func(const char* , int)
        func(ch, i);

        // 全特化
        int j = 13;
        double k = 13.1;
        func(j, k);
    }
} // namespace Namespace1

/*

Test2： 类模板偏特化

*/
namespace Namespace2
{
    // 泛化版本
    template <typename T, typename U>
    class A
    {
    public:
        A()
        {
            cout << "A()<typename T, typename U>" << endl;
        }
    };

    // 偏特化：范围上偏特化，T -> T*, U -> U*
    template <typename T, typename U>
    class A<T *, U *>
    {
    public:
        A()
        {
            cout << "A<T*, U*>()" << endl;
        }
    };

    // 全特化
    template <>
    class A<int, double>
    {
    public:
        A()
        {
            cout << "A<int, double>()" << endl;
        }
    };

    void test2()
    {
        // 泛化版本
        A<char, char> a1;

        // 范围偏特化版本
        A<char *, int *> a2;

        // 特化版本
        A<int, double> a3;
    }
} // namespace Namespace2

int main()
{
    // Namespace1::test1();
    Namespace2::test2();

    return 0;
}