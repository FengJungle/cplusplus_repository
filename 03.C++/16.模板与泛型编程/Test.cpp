#include <iostream>
using namespace std;

// 函数模板
template <typename T>
T returnMax(T a, T b)
{
    cout << "returnMax(T a, T b)" << endl;
    return a > b ? a : b;
}

// 全特化
template <>
int returnMax<int>(int a, int b)
{
    cout << "returnMax<int, int>(int a, int b)" << endl;
    return a > b ? a : b;
}

// 重载函数模板
template<typename T>
T returnMax(T a, T b, T c)
{
    cout<<"returnMax(T a, T b, T c)"<<endl;
    return returnMax(a, returnMax(b,c));
}

// 普通函数：如果参数个数和类型匹配，编译器将优先调用此函数
int returnMax(int a, int b)
{
    cout << "returnMax(int a, int b)" << endl;
    return a>b?a:b;
}

// 可变参数模板：递归调用
template<typename T, typename...Args>
T returnMax(T a, T b, Args...rset)
{
    cout<<"returnMax(T a, T b, Args...rset)"<<endl;
    returnMax(a>b?a:b,rset...);
}

// 默认模板实参
template<typename T, int size>
ostream& print(ostream& os, T a)
{
    for(int i=0;i<size;i++){
        os<<a<<"\t";
    }
    return os;
}

int main()
{
    // returnMax(10.2, 14.4);
    // returnMax<>(1,2);
    // returnMax(1,3);
    // returnMax<int>(10,20);
    // returnMax<double>(1,2);

    // returnMax(1,2,3);

    cout<<returnMax(1,2,3,4,5,121,012,3,24)<<endl;

    print<int, 5>(cout, 10);
    print<string, 3>(cout, "Good!");
}